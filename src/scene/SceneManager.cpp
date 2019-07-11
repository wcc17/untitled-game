#include "../../includes/scene/SceneManager.h"

void SceneManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Font* font) {
    this->eventBus = eventBus;

    collisionManager.initialize(eventBus);
    viewManager.initialize(eventBus);

    textureManager.loadTexture(AssetPath::PLAYER_TEXTURE);
    player.initialize(eventBus, textureManager.getTexture(AssetPath::PLAYER_TEXTURE));

    textureManager.loadTexture(AssetPath::DIALOGUE_BOX_TEXTURE);
    textManager.initialize(eventBus, textureManager.getTexture(AssetPath::DIALOGUE_BOX_TEXTURE), font);

    eventBus->subscribe(this, &SceneManager::onChangeSceneEvent);

    loadScene("scene1");
}

void SceneManager::update(sf::Time elapsedTime, sf::RenderWindow* window) {
    switch(state) {
        case SceneState::STATE_SCENE:
            updateSceneState(elapsedTime, window);
            break;
        case SceneState::STATE_CHANGING_SCENE:
            updateChangeSceneState();
            break;
    }
}

void SceneManager::updateSceneState(sf::Time elapsedTime, sf::RenderWindow* window) {
    player.update(elapsedTime, scene->getMapTileSize());
    npcManager.update(elapsedTime, scene->getMapTileSize());
    collisionManager.handleCollisions(player, npcManager.getNpcEntities(), scene->getMapCollidables());
    textManager.update(window, viewManager.getView(), elapsedTime);
}

void SceneManager::updateChangeSceneState() {
    releaseScene();
    loadScene(nextSceneName);
    nextSceneName = "";
    state = SceneState::STATE_SCENE;
}

void SceneManager::drawToRenderTexture(sf::RenderTexture* renderTexture) {
    switch(state) {
        case SceneState::STATE_SCENE:
            drawSceneStateToRenderTexture(renderTexture);
            break;
        case SceneState::STATE_CHANGING_SCENE:
            drawChangeSceneStateToRenderTexture(renderTexture);
            break;
    }
}

void SceneManager::drawSceneStateToRenderTexture(sf::RenderTexture* renderTexture) {
    renderTexture->setView(viewManager.getView());
    renderTexture->draw(*scene);
    npcManager.drawToRenderTexture(renderTexture);
    renderTexture->draw(player);
//    textManager.draw(window);
}

void SceneManager::drawChangeSceneStateToRenderTexture(sf::RenderTexture* renderTexture) {
}

void SceneManager::drawToRenderTextureWithDefaultView(sf::RenderTexture* renderTexture) {
//    window->setView(window->getDefaultView());
//    textManager.drawForDefaultView(window);
}

void SceneManager::loadScene(std::string sceneName) {
    scene = std::make_unique<Scene>();
    scene->initialize(sceneName, textureManager);

    player.initializeForScene(scene->getPlayerCollidable());

    npcManager.initialize(eventBus, scene->getNpcCollidables(), scene->getNpcMoveBoundariesMap(),
                          scene->getNpcNameToNpcAssetNameMap(), textureManager);

    std::vector<DialogueEvent> entityDialogueEvents = xmlManager.loadEntityDialogueForScene(sceneName);
    textManager.setEntityDialogueEvents(entityDialogueEvents);
}

void SceneManager::onChangeSceneEvent(ChangeSceneEvent* event) {
    this->nextSceneName = event->door.getName();
    this->state = SceneState::STATE_CHANGING_SCENE;
}

void SceneManager::release() {
    //TODO: don't forget to unsubscribe things from eventBus!

    textureManager.releaseTexture(AssetPath::PLAYER_TEXTURE);
    textureManager.releaseTexture(AssetPath::DIALOGUE_BOX_TEXTURE);
    releaseScene();
}

void SceneManager::releaseScene() {
    scene->release(textureManager);
    scene.reset();
    scene = nullptr;
    npcManager.release(textureManager);
}