#include "../../includes/scene/SceneManager.h"

const float SCENE_TRANSITION_SPEED = 1850.f;

void SceneManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Font* font, sf::Vector2u windowSize, sf::Vector2f defaultWindowSize) {
    this->eventBus = eventBus;
    this->font = font;
    this->windowSize = windowSize;
    this->defaultWindowSize = defaultWindowSize;

    viewManager.initialize(eventBus);

    eventBus->subscribe(this, &SceneManager::onChangeSceneToNewMapEvent, "SceneManager");
    eventBus->subscribe(this, &SceneManager::onChangeSceneToBattleEvent, "SceneManager");
    eventBus->subscribe(this, &SceneManager::onChangeSceneToPreviousSceneEvent, "SceneManager");
    eventBus->subscribe(this, &SceneManager::onOpenDialogueEvent, "SceneManager");
    eventBus->subscribe(this, &SceneManager::onControllerActionEvent, "SceneManager");
    eventBus->subscribe(this, &SceneManager::onControllerMenuEvent, "SceneManager");
    eventBus->subscribe(this, &SceneManager::onControllerCancelEvent, "SceneManager");
    eventBus->subscribe(this, &SceneManager::onControllerMenuMoveEvent, "SceneManager");
    loadScene("scene1");
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
            this->state = sceneStateHandler.getNextState(state);
            break;
    }
}

void SceneManager::updateSceneState(sf::Time elapsedTime, sf::RenderTexture& renderTexture) {
    scene->update(elapsedTime, renderTexture, viewManager.getView());
}

void SceneManager::updateSceneTransition(sf::Time elapsedTime) {
    float transitionSpeed = elapsedTime.asSeconds() * SCENE_TRANSITION_SPEED;
    if(state == SceneState::STATE_TRANSITION_SCENE_IN) {
        sceneAlpha += transitionSpeed;
        if(sceneAlpha >= 255.f) {
            sceneAlpha = 255.f;
            this->state = sceneStateHandler.getNextState(state);
        }
    } else if (state == SceneState::STATE_TRANSITION_SCENE_OUT) {
        sceneAlpha -= transitionSpeed;
        if(sceneAlpha <= 0.f) {
            sceneAlpha = 0.f;
            this->state = sceneStateHandler.getNextState(state);
        }
    }
}

void SceneManager::updateChangeSceneState() {
    //will only run once, just switching scenes
    loadScene(nextSceneName);
    this->nextSceneName = "";
    this->state = sceneStateHandler.getNextState(state);
}

void SceneManager::drawToRenderTexture(sf::RenderTexture* renderTexture) {
    switch(state) {
        case SceneState::STATE_SCENE:
        case SceneState::STATE_TRANSITION_SCENE_IN:
        case SceneState::STATE_TRANSITION_SCENE_OUT:
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
}

void SceneManager::loadScene(std::string sceneName) {
    if(scene != nullptr) {
        this->previousSceneName = scene->getSceneName();
        releaseScene();
    }

    if(sceneName == "battle") {
        scene = std::make_unique<BattleScene>();
    } else {
        scene = std::make_unique<OverworldScene>();
    }

    scene->initialize(eventBus, sceneName, this->previousSceneName, textureManager, font, windowSize, defaultWindowSize);
}

void SceneManager::onChangeSceneToNewMapEvent(ChangeSceneToNewMapEvent* event) {
    if(state == STATE_SCENE) {
        this->nextSceneName = event->newSceneName;
        this->state = sceneStateHandler.getNextState(state);
    }
}

void SceneManager::onChangeSceneToBattleEvent(ChangeSceneToBattleEvent* event) {
    if(state == STATE_SCENE) {
        this->nextSceneName = "battle";
        this->state = sceneStateHandler.getNextState(state);
    }
}

void SceneManager::onChangeSceneToPreviousSceneEvent(ChangeSceneToPreviousSceneEvent* event) {
    if(state == STATE_SCENE) {
        this->nextSceneName = this->previousSceneName;
        this->state = sceneStateHandler.getNextState(state);
    }
}

void SceneManager::onOpenDialogueEvent(OpenDialogueEvent *event) {
    scene->openDialogue(event->interactedWith.getName());
}

void SceneManager::onControllerMenuEvent(ControllerMenuEvent *event) {
    scene->handleControllerMenuButtonPressed();
}

void SceneManager::onControllerActionEvent(ControllerActionEvent *event) {
    scene->handleControllerActionButtonPressed();
}

void SceneManager::onControllerCancelEvent(ControllerCancelEvent *event) {
    scene->handleControllerCancelButtonPressed();
}

void SceneManager::onControllerMenuMoveEvent(ControllerMenuMoveEvent *event) {
    scene->handleControllerMenuMoveButtonPressed(event->direction);
}

sf::Color SceneManager::getSceneTransparency(sf::Color currentColor) {
    sf::Color newColor = sf::Color(currentColor.r, currentColor.g, currentColor.b, sceneAlpha);
    return newColor;
}

void SceneManager::release() {
    eventBus->unsubscribeInstanceFromAllEventTypes(this);

    textureManager.releaseTexture(AssetPath::PLAYER_TEXTURE);
    releaseScene();
}

void SceneManager::releaseScene() {
    scene->release(textureManager);
    scene.reset();
    scene = nullptr;
}