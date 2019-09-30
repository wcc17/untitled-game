#include "../../includes/npc/NpcManager.h"

static const std::string NPC_TYPE_HUMAN = "human";
static const std::string NPC_TYPE_CAT = "cat";
static const std::string NPC_TYPE_MONSTER = "monster";

void NpcManager::initialize(const std::shared_ptr<EventBus> eventBus,
                            const std::vector<Collidable>& collidables,
                            const std::map<std::string, sf::IntRect>& npcMoveBoundaries,
                            const std::map<std::string, std::vector<tmx::Property>>& npcNameToPropertiesMap,
                            const sf::Vector2u& mapTileSize,
                            TextureManager& textureManager) {
    this->eventBus = eventBus;
    this->mapTileSize = mapTileSize;

    for(Collidable collidable : collidables) {
        initializeNpc(textureManager, collidable, npcMoveBoundaries, npcNameToPropertiesMap);
    }

    eventBus->subscribe(this, &NpcManager::onOpenDialogueEvent);
    eventBus->subscribe(this, &NpcManager::onCloseDialogueEvent);
    eventBus->subscribe(this, &NpcManager::onNpcCollisionEvent);
}

void NpcManager::update(sf::Time deltaTime) {
    for(std::shared_ptr<NpcEntity> npc : npcs) {
        npc->update(deltaTime, mapTileSize);
    }
}

void NpcManager::drawToRenderTexture(sf::RenderTexture* renderTexture) {
    for(std::shared_ptr<NpcEntity> npc : npcs) {
        renderTexture->draw(*npc);
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
            npc->onCollisionEvent(event->newNpcPosition);
            break;
        }
    }
}

void NpcManager::initializeNpc(
        TextureManager& textureManager,
        const Collidable& collidable,
        const std::map<std::string, sf::IntRect>& npcMoveBoundaries,
        const std::map<std::string, std::vector<tmx::Property>>& npcNameToPropertiesMap) {

    std::vector<tmx::Property> npcProperties = npcNameToPropertiesMap.at(collidable.getName());
    sf::IntRect moveBoundaries = npcMoveBoundaries.at(collidable.getName());
    NpcType npcType = getNpcTypeFromString(Map::getObjectPropertyStringValue(Map::PROPERTY_NAME_NPC_TYPE, npcProperties));
    std::string assetName = Map::getObjectPropertyStringValue(Map::PROPERTY_NAME_ASSET_NAME, npcProperties);
    bool isAggressive = Map::getObjectPropertyBoolValue(Map::PROPERTY_NAME_IS_AGGRESSIVE, npcProperties);
    sf::Texture* texture = loadAndRetrieveNpcTexture(assetName, textureManager);

    std::shared_ptr<NpcEntity> npcEntity = getNewNpcEntityFromType(npcType);
    npcEntity->initialize(texture, collidable, moveBoundaries, assetName, isAggressive, npcType);
    npcs.push_back(npcEntity);
}

sf::Texture* NpcManager::loadAndRetrieveNpcTexture(std::string assetName, TextureManager& textureManager) {
    std::string assetFilePath = AssetPath::getNpcAssetPath(assetName);
    textureManager.loadTexture(assetFilePath);
    return textureManager.getTexture(assetFilePath);
}

NpcType NpcManager::getNpcTypeFromString(std::string npcTypeString) {
    if(NPC_TYPE_HUMAN == npcTypeString) {
        return NpcType::HUMAN;
    } else if(NPC_TYPE_CAT == npcTypeString) {
        return NpcType::CAT;
    } else if(NPC_TYPE_MONSTER == npcTypeString) {
        return NpcType::MONSTER;
    } else {
        return NpcType::NO_NPC_TYPE;
    }
}

std::shared_ptr<NpcEntity> NpcManager::getNewNpcEntityFromType(NpcType npcType) {
    switch(npcType) {
        case NpcType::HUMAN:
            return std::make_shared<HumanNpcEntity>();
        case NpcType::CAT:
            return std::make_shared<CatNpcEntity>();
        case NpcType::MONSTER:
            return std::make_shared<MonsterNpcEntity>();
        case NpcType::NO_NPC_TYPE:
            return std::make_shared<HumanNpcEntity>();
    }
}

void NpcManager::releaseNpcTextures(std::string assetName, TextureManager& textureManager) {
    textureManager.releaseTexture(AssetPath::getNpcAssetPath(assetName));
}

std::vector<std::shared_ptr<NpcEntity>>& NpcManager::getNpcEntities() {
    return this->npcs;
}

void NpcManager::release(TextureManager& textureManager) {
    eventBus->unsubscribe(this, &NpcManager::onOpenDialogueEvent);
    eventBus->unsubscribe(this, &NpcManager::onCloseDialogueEvent);
    eventBus->unsubscribe(this, &NpcManager::onNpcCollisionEvent);

    for(std::shared_ptr<NpcEntity> npc : npcs) {
        releaseNpcTextures(npc->getAssetName(), textureManager);
    }
    npcs.clear();
}
