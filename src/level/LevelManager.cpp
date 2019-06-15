#include "../../includes/level/LevelManager.h"

void LevelManager::initialize(std::shared_ptr<EventBus> eventBus) {
    scene.initialize(AssetPath::LEVEL_TILEMAP); //TODO: this should be decided else where when switching level logic is implemented. Probably in a GameManager one level up

    viewManager.initialize(eventBus);
    viewManager.initializeViewForLevel(scene.getMapSizeInPixels());

    textureManager.loadTexture(AssetPath::PLAYER_TEXTURE);
    player.initialize(textureManager.getTexture(AssetPath::PLAYER_TEXTURE), scene.getMapSizeInPixels().x,
                      scene.getMapSizeInPixels().y, eventBus);

    textureManager.loadTexture(AssetPath::NPC_TEXTURE);
    npcManager.initialize(scene.getNpcCollidables(), textureManager.getTexture(AssetPath::PLAYER_TEXTURE));

    collisionManager.initialize(eventBus);
}

void LevelManager::update(sf::Time elapsedTime) {
    viewManager.update(elapsedTime);
    player.update(elapsedTime);
    collisionManager.handleCollisions(getEntityCollidables(), scene.getMapCollidables());
}

void LevelManager::draw(sf::RenderWindow* window) {
    window->setView(viewManager.getView());
    window->draw(scene);
    npcManager.draw(window);
    window->draw(player);
}

std::vector<Collidable> LevelManager::getEntityCollidables() {
    //NOTE: recreating this vector every frame. Pointers might be better, but then I'll have to worry about
    //removing (dead, removed?) entities from it when NPCs are introduced
    std::vector<Collidable> entityCollidables;
    entityCollidables.push_back(player);

//    for(NpcEntity entity : npcManager.getNpcEntities()) {
//        entityCollidables.push_back(entity);
//    }

    return entityCollidables;
}

//TODO: should all of the "release" methods be in deconstructors instead? Some classes its not appropriate, but this one it is
void LevelManager::release() {
    textureManager.releaseTextures();
    scene.release(); //TODO: will eventually be called somewhere else when the level changes
}