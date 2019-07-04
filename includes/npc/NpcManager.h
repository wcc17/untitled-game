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

class NpcManager {

public:
    void initialize(std::shared_ptr<EventBus> eventBus, std::vector<Collidable> collidables, sf::Texture* texture, std::map<std::string, sf::IntRect> npcMoveBoundaries);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void draw(sf::RenderWindow* window);
    std::vector<std::shared_ptr<NpcEntity>>& getNpcEntities();
    void release();
private:
    std::shared_ptr<EventBus> eventBus;
    std::vector<std::shared_ptr<NpcEntity>> npcs;
    std::map<std::string, sf::IntRect> npcMoveBoundaries;
    void initializeNpc(Collidable& collidable, sf::Texture* texture);
    void onOpenDialogueEvent(OpenDialogueEvent* event);
    void onCloseDialogueEvent(CloseDialogueEvent* event);
    void onNpcCollisionEvent(NpcCollisionEvent* event);
};


#endif //NEWNEW_NPCMANAGER_H
