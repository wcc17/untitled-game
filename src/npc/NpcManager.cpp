#include "../../includes/npc/NpcManager.h"

void NpcManager::initialize(std::vector<Collidable> collidables, sf::Texture* texture) { //TODO: the texture will not be passed to NpcManager unless its in a vector of texture references for the different NPCs (theres only 1 for now)
    for(Collidable collidable : collidables) {
        NpcEntity* npcEntity = new NpcEntity();
        npcEntity->initialize(texture, collidable.getName(), collidable.getType(), collidable.getBoundingBox()); //TODO: obviously need a better way to assign textures
        npcEntity->stop();
        npcs.push_back(npcEntity);
    }
}

void NpcManager::update(sf::Time deltaTime) {
    for(NpcEntity* npc : npcs) {
        npc->update(deltaTime);
    }
}

void NpcManager::draw(sf::RenderWindow* window) {
    for(NpcEntity* npc : npcs) {
        window->draw(*npc);
    }
}

std::vector<NpcEntity*> NpcManager::getNpcEntities() {
    return this->npcs;
}
