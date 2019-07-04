#ifndef NEWNEW_COLLISIONMANAGER_H
#define NEWNEW_COLLISIONMANAGER_H

#include <vector>
#include "../events/EventBus.h"
#include "Collidable.h"
#include "../entity/npc/NpcEntity.h"
#include "../entity/player/Player.h"
#include "../events/event/PlayerCollisionEvent.h"
#include "../events/event/PlayerVicinityCollisionEvent.h"
#include "../events/event/NpcCollisionEvent.h"

class CollisionManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void handleCollisions(Player& player,
            const std::vector<std::shared_ptr<NpcEntity>>& entities,
            const std::vector<std::shared_ptr<Collidable>>& mapCollidables);

private:
    std::shared_ptr<EventBus> eventBus;

    void handlePlayerCollisions(Player& player, const std::vector<std::shared_ptr<NpcEntity>>& entities, const std::vector<std::shared_ptr<Collidable>>& mapCollidables);
    bool publishCollisionsWithPlayerAndMap(Player& player, const std::vector<std::shared_ptr<Collidable>>& collidables);
    bool publishCollisionsWithPlayerAndEntities(Player& player, const std::vector<std::shared_ptr<NpcEntity>>& entities);

    void handleEntityCollisions(Player& player, const std::vector<std::shared_ptr<NpcEntity>>& entities, const std::vector<std::shared_ptr<Collidable>>& mapCollidables);
    void initializeEntityCollidedMap(const std::vector<std::shared_ptr<NpcEntity>>& entities, std::map<std::string, bool>& hasEntityCollidedMap);
    void publishCollisionBetweenEntitiesAndPlayer(Player& player, const std::vector<std::shared_ptr<NpcEntity>>& entities, std::map<std::string, bool>& hasEntityCollidedMap);
    void publishCollisionsBetweenEntitiesAndMap(const std::vector<std::shared_ptr<NpcEntity>>& entities, const std::vector<std::shared_ptr<Collidable>>& collidables, std::map<std::string, bool>& hasEntityCollidedMap);

    static bool collisionOccurred(const Collidable& collidable1, const Collidable& collidable2);
    static bool playerVicinityCollisionOccurred(Player& player, const Collidable& collidable);
};


#endif //NEWNEW_COLLISIONMANAGER_H
