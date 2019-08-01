#include "../../includes/scene/SceneManager.h"

const float SCENE_TRANSITION_SPEED = 1850.f;

void SceneManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Font* font, sf::Vector2u windowSize, sf::Vector2f defaultWindowSize) {
    this->eventBus = eventBus;

    collisionManager.initialize(eventBus);
    viewManager.initialize(eventBus);

    textureManager.loadTexture(AssetPath::PLAYER_TEXTURE);
    player.initialize(eventBus, textureManager.getTexture(AssetPath::PLAYER_TEXTURE));

    uiManager.initialize(eventBus, textureManager, font, windowSize, defaultWindowSize);

    eventBus->subscribe(this, &SceneManager::onChangeSceneEvent);
    eventBus->subscribe(this, &SceneManager::onOpenMenuEvent);
    eventBus->subscribe(this, &SceneManager::onCloseMenuEvent);
    loadScene("", "scene1");
}

void SceneManager::update(sf::Time elapsedTime, sf::RenderTexture& renderTexture) {
    switch(state) {
        case SceneState::STATE_SCENE:
            updateSceneState(elapsedTime, renderTexture);
            break;
        case SceneState::STATE_TRANSITION_SCENE_IN:
        case SceneState::STATE_TRANSITION_SCENE_OUT:
            updateSceneState(elapsedTime, renderTexture);
            updateSceneTransition(elapsedTime);
            break;
        case SceneState::STATE_CHANGING_SCENE:
            updateChangeSceneState();
            break;
        case SceneState::STATE_SKIP_FRAME:
            //skip a frame so that everything can catch up after loading a new scene
            setNextScene();
        case SceneState::STATE_PAUSE:
            updatePauseState(elapsedTime, renderTexture);
            break;
    }
}

void SceneManager::updateSceneState(sf::Time elapsedTime, sf::RenderTexture& renderTexture) {
    player.update(elapsedTime, scene->getMapTileSize());
    npcManager.update(elapsedTime, scene->getMapTileSize());
    collisionManager.handleCollisions(player, npcManager.getNpcEntities(), scene->getMapCollidables());
    uiManager.update(renderTexture, viewManager.getView(), elapsedTime);
}

void SceneManager::updateSceneTransition(sf::Time elapsedTime) {
    float transitionSpeed = elapsedTime.asSeconds() * SCENE_TRANSITION_SPEED;
    if(state == SceneState::STATE_TRANSITION_SCENE_IN) {
        sceneAlpha += transitionSpeed;
        if(sceneAlpha >= 255.f) {
            sceneAlpha = 255.f;
            setNextScene();
        }
    } else if (state == SceneState::STATE_TRANSITION_SCENE_OUT) {
        sceneAlpha -= transitionSpeed;
        if(sceneAlpha <= 0.f) {
            sceneAlpha = 0.f;
            setNextScene();
        }
    }
}

void SceneManager::updateChangeSceneState() {
    //will only run once, just switching scenes
    std::string previousSceneName = scene->getSceneName();
    releaseScene();
    loadScene(previousSceneName, nextSceneName);
    nextSceneName = "";
    setNextScene();
}

void SceneManager::updatePauseState(sf::Time elapsedTime, sf::RenderTexture& renderTexture) {
    uiManager.update(renderTexture, viewManager.getView(), elapsedTime);
}

void SceneManager::drawToRenderTexture(sf::RenderTexture* renderTexture) {
    switch(state) {
        case SceneState::STATE_SCENE:
        case SceneState::STATE_TRANSITION_SCENE_IN:
        case SceneState::STATE_TRANSITION_SCENE_OUT:
        case SceneState::STATE_PAUSE:
            drawSceneStateToRenderTexture(renderTexture);
            break;
        case SceneState::STATE_CHANGING_SCENE:
        case SceneState::STATE_SKIP_FRAME:
//            drawChangeSceneStateToRenderTexture(renderTexture);
            break;
    }
}

void SceneManager::drawSceneStateToRenderTexture(sf::RenderTexture* renderTexture) {
    renderTexture->setView(viewManager.getView());
    renderTexture->draw(*scene);
    renderTexture->draw(player);
    npcManager.drawToRenderTexture(renderTexture);
    uiManager.drawToRenderTexture(renderTexture);
}

void SceneManager::loadScene(std::string previousSceneName, std::string sceneName) {
    scene = std::make_unique<Scene>();
    scene->initialize(sceneName, textureManager);
    std::string spawnName = scene->getPlayerSpawnPointName(previousSceneName);

    player.initializeForScene(scene->getPlayerCollidable(spawnName));

    npcManager.initialize(eventBus, scene->getNpcCollidables(), scene->getNpcMoveBoundariesMap(),
                          scene->getNpcNameToNpcAssetNameMap(), textureManager);

    std::vector<DialogueEvent> entityDialogueEvents = xmlManager.loadEntityDialogueForScene(sceneName);
    uiManager.resetOnNewScene(entityDialogueEvents);
}

void SceneManager::setNextScene() {
    //transition in > change scene > scene > transition out > change scene > transition in > ......
    switch(state) {
        case STATE_SCENE:
            state = STATE_TRANSITION_SCENE_OUT;
            break;
        case STATE_TRANSITION_SCENE_OUT:
            state = STATE_CHANGING_SCENE;
            break;
        case STATE_CHANGING_SCENE:
            state = STATE_SKIP_FRAME;
            break;
        case STATE_SKIP_FRAME:
            state = STATE_TRANSITION_SCENE_IN;
            break;
        case STATE_TRANSITION_SCENE_IN:
            state = STATE_SCENE;
            break;
        default:
            break;
    }
}

void SceneManager::onChangeSceneEvent(ChangeSceneEvent* event) {
    if(state == STATE_SCENE) {
        this->nextSceneName = event->door.getName();
        setNextScene();
    }
}

void SceneManager::onOpenMenuEvent(OpenMenuEvent* event) {
    if(state == STATE_SCENE) {
        state = STATE_PAUSE;
    } else {
        uiManager.resetMenu(); //TODO: this is sort of a hack because KeyboardController is in Game.cpp and I can't keep the user from pressing menu button during scene transitions
    }
}

void SceneManager::onCloseMenuEvent(CloseMenuEvent* event) {
    if(state == STATE_PAUSE) {
        state = STATE_SCENE;
    }
}

sf::Color SceneManager::getSceneTransparency(sf::Color currentColor) {
    sf::Color newColor = sf::Color(currentColor.r, currentColor.g, currentColor.b, sceneAlpha);
    return newColor;
}

void SceneManager::release() {
    //TODO: don't forget to unsubscribe things from eventBus!

    textureManager.releaseTexture(AssetPath::PLAYER_TEXTURE);
    uiManager.release(textureManager);
    releaseScene();
}

void SceneManager::releaseScene() {
    scene->release(textureManager);
    scene.reset();
    scene = nullptr;
    npcManager.release(textureManager);
}