#ifndef NEWNEW_NPCMANAGER_H
#define NEWNEW_NPCMANAGER_H

#include "../entity/npc/NpcEntity.h"
#include "../../includes/asset/AssetPath.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "../events/EventBus.h"
#include "../../includes/events/event/CloseDialogueEvent.h"
#include "../../includes/events/event/OpenDialogueEvent.h"
#include "../../includes/events/event/ExitGameEvent.h"
#include "../events/event/NpcCollisionEvent.h"
#include "../asset/TextureManager.h"
#include <tmxlite/Property.hpp>
#include "../../includes/map/Map.h"
#include "../entity/npc/types/NpcType.h"
#include "../../includes/entity/npc/types/MonsterNpcEntity.h"
#include "../../includes/entity/npc/types/HumanNpcEntity.h"
#include "../../includes/entity/npc/types/CatNpcEntity.h"

class NpcManager {

public:
    void initialize(const std::shared_ptr<EventBus> eventBus,
                    const std::vector<Collidable>& collidables,
                    const std::map<std::string, sf::IntRect>& npcMoveBoundaries,
                    const std::map<std::string, std::vector<tmx::Property>>& npcNameToPropertiesMap,
                    const sf::Vector2u& mapTileSize,
                    TextureManager& textureManager);
    void update(sf::Time deltaTime);
    void drawToRenderTexture(sf::RenderTexture& renderTexture) const;
    std::vector<std::shared_ptr<NpcEntity>>& getNpcEntities();
    void release(TextureManager& textureManager);
private:
    std::shared_ptr<EventBus> eventBus;
    std::vector<std::shared_ptr<NpcEntity>> npcs;
    sf::Vector2u mapTileSize;

    void initializeNpc(
            TextureManager& textureManager,
            const Collidable& collidable,
            const std::map<std::string, sf::IntRect>& npcMoveBoundaries,
            const std::map<std::string, std::vector<tmx::Property>>& npcNameToPropertiesMap);
    void onOpenDialogueEvent(OpenDialogueEvent* event);
    void onCloseDialogueEvent(CloseDialogueEvent* event);
    void onNpcCollisionEvent(NpcCollisionEvent* event);
    sf::Texture* loadAndRetrieveNpcTexture(std::string assetName, TextureManager& textureManager);
    NpcType getNpcTypeFromString(std::string npcTypeString);
    std::shared_ptr<NpcEntity> getNewNpcEntityFromType(NpcType npcType);
    void releaseNpcTextures(std::string assetName, TextureManager& textureManager);
};


#endif //NEWNEW_NPCMANAGER_H
