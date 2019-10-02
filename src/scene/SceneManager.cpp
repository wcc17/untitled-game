#include "../../includes/scene/SceneManager.h"

const float SCENE_TRANSITION_SPEED = 1850.f;

void SceneManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Font* font, sf::Vector2u windowSize, sf::Vector2f defaultWindowSize) {
    this->eventBus = eventBus;

    uiManager.initialize(eventBus, textureManager, font, windowSize, defaultWindowSize);
    viewManager.initialize(eventBus);

    eventBus->subscribe(this, &SceneManager::onChangeSceneEvent, "SceneManager");
    eventBus->subscribe(this, &SceneManager::onOpenMenuEvent, "SceneManager");
    eventBus->subscribe(this, &SceneManager::onCloseMenuEvent, "SceneManager");
    eventBus->subscribe(this, &SceneManager::onAggressiveNpcCollisionEvent, "SceneManager");
    loadScene("", "scene1");
}

void SceneManager::update(sf::Time elapsedTime, sf::RenderTexture& renderTexture) {
    switch(state) {
        case SceneState::STATE_OVERWORLD_SCENE:
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
    scene->update(elapsedTime);
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
        case SceneState::STATE_OVERWORLD_SCENE:
        case SceneState::STATE_TRANSITION_SCENE_IN:
        case SceneState::STATE_TRANSITION_SCENE_OUT:
        case SceneState::STATE_PAUSE:
            drawSceneStateToRenderTexture(renderTexture);
            break;
        case SceneState::STATE_CHANGING_SCENE:
        case SceneState::STATE_SKIP_FRAME:
            break;
    }
}

void SceneManager::drawSceneStateToRenderTexture(sf::RenderTexture* renderTexture) {
    renderTexture->setView(viewManager.getView());
    renderTexture->draw(*scene);
    uiManager.drawToRenderTexture(renderTexture);
}

void SceneManager::loadScene(std::string previousSceneName, std::string sceneName) {
    scene = std::make_unique<OverworldScene>();
    scene->initialize(eventBus, sceneName, previousSceneName, textureManager);
    std::vector<DialogueEvent> entityDialogueEvents = xmlManager.loadEntityDialogueForScene(sceneName);
    uiManager.resetOnNewScene(entityDialogueEvents);
}

void SceneManager::setNextScene() {
    //transition in > change scene > scene > transition out > change scene > transition in > ......
    switch(state) {
        case STATE_OVERWORLD_SCENE:
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
            state = STATE_OVERWORLD_SCENE;
            break;
        default:
            break;
    }
}

void SceneManager::onChangeSceneEvent(ChangeSceneEvent* event) {
    if(state == STATE_OVERWORLD_SCENE) {
        this->nextSceneName = event->door.getName();
        setNextScene();
    }
}

void SceneManager::onOpenMenuEvent(OpenMenuEvent* event) {
    if(state == STATE_OVERWORLD_SCENE) {
        state = STATE_PAUSE;
    }
}

void SceneManager::onCloseMenuEvent(CloseMenuEvent* event) {
    if(state == STATE_PAUSE) {
        state = STATE_OVERWORLD_SCENE;
    }
}

void SceneManager::onAggressiveNpcCollisionEvent(AggressiveNpcCollisionEvent* event) {
    //start up the battle scene
//    sceneToReturnToAfterBattle = std::move(scene);
//    scene = battleScene;
}

sf::Color SceneManager::getSceneTransparency(sf::Color currentColor) {
    sf::Color newColor = sf::Color(currentColor.r, currentColor.g, currentColor.b, sceneAlpha);
    return newColor;
}

void SceneManager::release() {
    eventBus->unsubscribeInstanceFromAllEventTypes(this);

    textureManager.releaseTexture(AssetPath::PLAYER_TEXTURE);
    uiManager.release(textureManager);
    releaseScene();
}

void SceneManager::releaseScene() {
    scene->release(textureManager);
    scene.reset();
    scene = nullptr;
}