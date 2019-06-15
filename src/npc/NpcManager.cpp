#include "../../includes/npc/NpcManager.h"

void NpcManager::initialize(std::vector<Collidable> collidables, sf::Texture* texture) { //TODO: the texture will not be passed to NpcManager unless its in a vector of texture references for the different NPCs (theres only 1 for now)

//    NpcEntity npcEntity;

//    for(Collidable collidable : collidables) {
//        NpcEntity npcEntity = collidable;
//        npcEntity.initialize(texture); //TODO: obviously need a better way to assign textures
//        npcs.push_back(npcEntity);
//    }
}

void NpcManager::draw(sf::RenderWindow* window) {
//    for(NpcEntity npc : npcs) {
//        window->draw(npc);
//    }
}

//std::vector<NpcEntity> NpcManager::getNpcEntities() {
//    return this->npcs;
//}
