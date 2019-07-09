#include "../../includes/scene/SceneManager.h"

void SceneManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Font* font) {
    this->eventBus = eventBus;

    collisionManager.initialize(eventBus);
    viewManager.initialize(eventBus);

    textureManager.loadTexture(AssetPath::PLAYER_TEXTURE);
    player.initialize(eventBus, textureManager.getTexture(AssetPath::PLAYER_TEXTURE));

    textureManager.loadTexture(AssetPath::DIALOGUE_BOX_TEXTURE);
    textManager.initialize(eventBus, textureManager.getTexture(AssetPath::DIALOGUE_BOX_TEXTURE), font);

    loadScene("scene1");
}

void SceneManager::loadScene(std::string sceneName) {
    scene = std::make_unique<Scene>(); //TODO: make sure scene is reset before this happens
    scene->initialize(sceneName, textureManager); //TODO: make sure scene is reset before this happens

    player.initializeForScene(scene->getPlayerCollidable());

    npcManager.initialize(eventBus, scene->getNpcCollidables(), scene->getNpcMoveBoundariesMap(),
            scene->getNpcNameToNpcAssetNameMap(), textureManager); //TODO: make sure that this can be re-initialized without throwing the old npcManager away. probably needs a release function or something. TODO: any good alternatives to passing textureManager?

    std::vector<DialogueEvent> entityDialogueEvents = xmlManager.loadEntityDialogueForScene(sceneName);
    textManager.setEntityDialogueEvents(entityDialogueEvents);
}

void SceneManager::update(sf::Time elapsedTime, sf::RenderWindow* window) {
    player.update(elapsedTime, scene->getMapTileSize());
    npcManager.update(elapsedTime, scene->getMapTileSize());
    collisionManager.handleCollisions(player, npcManager.getNpcEntities(), scene->getMapCollidables());
    textManager.update(window, viewManager.getView(), elapsedTime);
}

void SceneManager::draw(sf::RenderWindow* window) {
    window->setView(viewManager.getView());
    window->draw(*scene);
    npcManager.draw(window);
    window->draw(player);
    textManager.draw(window);
}

void SceneManager::drawForDefaultView(sf::RenderWindow* window) {
    window->setView(window->getDefaultView());
    textManager.drawForDefaultView(window);
}

void SceneManager::release() {
    //TODO: don't forget to unsubscribe things from eventBus!

    textureManager.releaseTexture(AssetPath::PLAYER_TEXTURE);
    textureManager.releaseTexture(AssetPath::DIALOGUE_BOX_TEXTURE);

    scene->release(textureManager); //TODO: will eventually be called somewhere else when the scene changes
    scene.reset();  //TODO: will eventually be called somewhere else when the scene changes

    npcManager.release(textureManager);
}