#include "../../includes/npc/NpcManager.h"

void NpcManager::initialize(std::vector<Collidable> collidables, sf::Texture* texture) { //TODO: the texture will not be passed to NpcManager unless its in a vector of texture references for the different NPCs (theres only 1 for now)
    for(Collidable collidable : collidables) {
        std::shared_ptr<NpcEntity> npcEntity = std::make_shared<NpcEntity>();
        npcEntity->initialize(texture, collidable); //TODO: obviously need a better way to assign textures
        npcEntity->stop();
        npcs.push_back(npcEntity);
    }
}

void NpcManager::update(sf::Time deltaTime) {
    for(std::shared_ptr<NpcEntity> npc : npcs) {
        npc->update(deltaTime);
    }
}

void NpcManager::draw(sf::RenderWindow* window) {
    for(std::shared_ptr<NpcEntity> npc : npcs) {
        window->draw(*npc);
    }
}

std::vector<std::shared_ptr<NpcEntity>>& NpcManager::getNpcEntities() {
    return this->npcs;
}

void NpcManager::release() {
    npcs.clear();
}
