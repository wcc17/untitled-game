#include "../../includes/npc/NpcManager.h"

void NpcManager::initialize(std::shared_ptr<EventBus> eventBus, std::vector<Collidable> collidables, sf::Texture* texture) { //TODO: the texture will not be passed to NpcManager unless its in a vector of texture references for the different NPCs (theres only 1 for now)
    this->eventBus = eventBus;

    for(Collidable collidable : collidables) {
        std::shared_ptr<NpcEntity> npcEntity = std::make_shared<NpcEntity>();
        npcEntity->initialize(texture, collidable); //TODO: obviously need a better way to assign textures to npcs
        npcEntity->stop();
        npcs.push_back(npcEntity);
    }

    eventBus->subscribe(this, &NpcManager::onStartEntityDialogueEvent);
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

void NpcManager::onStartEntityDialogueEvent(StartEntityDialogueEvent* event) {
    for(std::shared_ptr<NpcEntity> npc : npcs) {
        if(event->npcName == npc->getName()) {
            npc->turnToFacePlayer(event->playerFacingDirection);
            break;
        }
    }
}

void NpcManager::release() {
    npcs.clear();
}

std::vector<std::shared_ptr<NpcEntity>>& NpcManager::getNpcEntities() {
    return this->npcs;
}
