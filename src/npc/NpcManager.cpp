#include "../../includes/npc/NpcManager.h"
#include "../../includes/events/event/ExitGameEvent.h"

void NpcManager::initialize(std::shared_ptr<EventBus> eventBus,
                            std::vector<Collidable> collidables,
                            sf::Texture* texture, //TODO: the texture will not be passed to NpcManager unless its in a vector of texture references for the different NPCs (theres only 1 for now)
                            std::map<std::string, sf::IntRect> npcMoveBoundaries) {
    this->eventBus = eventBus;
    this->npcMoveBoundaries = npcMoveBoundaries;

    for(Collidable collidable : collidables) {
        initializeNpc(collidable, texture);
    }

    eventBus->subscribe(this, &NpcManager::onStartEntityDialogueEvent);
}

void NpcManager::update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    for(std::shared_ptr<NpcEntity> npc : npcs) {

        npc->update(deltaTime, mapTileSize);
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

void NpcManager::initializeNpc(Collidable& collidable, sf::Texture* texture) {
    std::shared_ptr<NpcEntity> npcEntity = std::make_shared<NpcEntity>();

    try {
        npcEntity->initialize(texture, collidable, npcMoveBoundaries.at(collidable.getName())); //TODO: obviously need a better way to assign textures to npcs
    } catch (const std::out_of_range& e) {
        std::string exitMessage = "Entity " + collidable.getName() + " is not assigned a move boundary. Exiting\n";
        eventBus->publish(new ExitGameEvent(exitMessage));
    }

    npcEntity->stop();
    npcs.push_back(npcEntity);
}

std::vector<std::shared_ptr<NpcEntity>>& NpcManager::getNpcEntities() {
    return this->npcs;
}
