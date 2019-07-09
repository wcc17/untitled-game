#include "../../includes/npc/NpcManager.h"

void NpcManager::initialize(std::shared_ptr<EventBus> eventBus,
                            std::vector<Collidable> collidables,
                            std::map<std::string, sf::IntRect> npcMoveBoundaries,
                            std::map<std::string, std::string> npcNameToNpcAssetNameMap,
                            TextureManager& textureManager) {
    this->eventBus = eventBus;

    for(Collidable collidable : collidables) {
        std::string assetName = npcNameToNpcAssetNameMap.at(collidable.getName());
        sf::IntRect moveBoundaries = npcMoveBoundaries.at(collidable.getName());
        sf::Texture* texture = loadAndRetrieveNpcTexture(assetName, textureManager);
        initializeNpc(collidable, moveBoundaries, texture, assetName);
    }

    eventBus->subscribe(this, &NpcManager::onOpenDialogueEvent);
    eventBus->subscribe(this, &NpcManager::onCloseDialogueEvent);
    eventBus->subscribe(this, &NpcManager::onNpcCollisionEvent);
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

//TODO: stop writing out this for loop for every single function that needs to look at all of the npcs. Or put the NPCs in a map?
void NpcManager::onOpenDialogueEvent(OpenDialogueEvent* event) {
    if(event->interactedWith.getType() == ObjectType::NPC) {
        for(std::shared_ptr<NpcEntity> npc : npcs) {
            if(event->interactedWith.getName() == npc->getEntityCollidable().getName()) {
                npc->onPlayerInteractionStart(event->playerFacingDirection);
                break;
            }
        }
    }
}

void NpcManager::onCloseDialogueEvent(CloseDialogueEvent* event) {
    if(event->interactedWith.getType() == ObjectType::NPC) {
        for(std::shared_ptr<NpcEntity> npc : npcs) {
            if(event->interactedWith.getName() == npc->getEntityCollidable().getName()) {
                npc->onPlayerInteractionFinish();
                break;
            }
        }
    }
}

void NpcManager::onNpcCollisionEvent(NpcCollisionEvent* event) {
    for(std::shared_ptr<NpcEntity> npc : npcs) {
        if(event->npc.getEntityCollidable().getName() == npc->getEntityCollidable().getName()) {
            npc->onCollisionEvent(event->collidedWith);
            break;
        }
    }
}

void NpcManager::initializeNpc(Collidable& collidable, sf::IntRect moveBoundaries, sf::Texture* texture, std::string assetName) {
    std::shared_ptr<NpcEntity> npcEntity = std::make_shared<NpcEntity>();
    try {
        npcEntity->initialize(texture, collidable, moveBoundaries, assetName);
    } catch (const std::out_of_range& e) {
        std::string exitMessage = "Entity " + collidable.getName() + " is not assigned a move boundary. Exiting";
        eventBus->publish(new ExitGameEvent(exitMessage));
    }

    npcs.push_back(npcEntity);
}

sf::Texture* NpcManager::loadAndRetrieveNpcTexture(std::string assetName, TextureManager& textureManager) {
    std::string assetFilePath = AssetPath::getNpcAssetPath(assetName);
    textureManager.loadTexture(assetFilePath);
    return textureManager.getTexture(assetFilePath);
}

void NpcManager::releaseNpcTextures(std::string assetName, TextureManager& textureManager) {
    textureManager.releaseTexture(AssetPath::getNpcAssetPath(assetName));
}

std::vector<std::shared_ptr<NpcEntity>>& NpcManager::getNpcEntities() {
    return this->npcs;
}

//TODO: this isn't being utilized yet
void NpcManager::release(TextureManager& textureManager) {
    //TODO: unsubscribe from event bus!

    for(std::shared_ptr<NpcEntity> npc : npcs) {
        releaseNpcTextures(npc->getAssetName(), textureManager);
    }
    npcs.clear();
}
