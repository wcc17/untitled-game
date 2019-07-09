#ifndef NEWNEW_NPCMANAGER_H
#define NEWNEW_NPCMANAGER_H

#include "../entity/npc/NpcEntity.h"
#include "../../includes/asset/AssetPath.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "../events/EventBus.h"
#include "../../includes/events/event/CloseDialogueEvent.h"
#include "../../includes/events/event/OpenDialogueEvent.h"
#include "../../includes/events/event/ExitGameEvent.h"
#include "../events/event/NpcCollisionEvent.h"
#include "../asset/TextureManager.h"

class NpcManager {

public:
    void initialize(std::shared_ptr<EventBus> eventBus,
                    std::vector<Collidable> collidables,
                    std::map<std::string, sf::IntRect> npcMoveBoundaries,
                    std::map<std::string, std::string> npcNameToNpcAssetNameMap,
                    TextureManager& textureManager);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void draw(sf::RenderWindow* window);
    std::vector<std::shared_ptr<NpcEntity>>& getNpcEntities();
    void release(TextureManager& textureManager);
private:
    std::shared_ptr<EventBus> eventBus;
    std::vector<std::shared_ptr<NpcEntity>> npcs;
    void initializeNpc(Collidable& collidable, sf::IntRect moveBoundaries, sf::Texture* texture, std::string assetName);
    void onOpenDialogueEvent(OpenDialogueEvent* event);
    void onCloseDialogueEvent(CloseDialogueEvent* event);
    void onNpcCollisionEvent(NpcCollisionEvent* event);
    sf::Texture* loadAndRetrieveNpcTexture(std::string assetName, TextureManager& textureManager);
    void releaseNpcTextures(std::string assetName, TextureManager& textureManager);
};


#endif //NEWNEW_NPCMANAGER_H
