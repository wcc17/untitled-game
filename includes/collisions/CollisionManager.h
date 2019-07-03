#ifndef NEWNEW_COLLISIONMANAGER_H
#define NEWNEW_COLLISIONMANAGER_H

#include <vector>
#include "../events/EventBus.h"
#include "Collidable.h"
#include "../entity/character/NpcEntity.h"
#include "../entity/player/Player.h"
#include "../events/event/PlayerCollisionEvent.h"
#include "../events/event/PlayerVicinityCollisionEvent.h"

class CollisionManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void handleCollisions(const Player& player,
            const std::vector<std::shared_ptr<NpcEntity>>& entities,
            const std::vector<std::shared_ptr<Collidable>>& mapCollidables);

private:
    std::shared_ptr<EventBus> eventBus;
    bool publishCollisionsWithPlayerAndMap(const Player& player, const std::vector<std::shared_ptr<Collidable>>& collidables);
    bool publishCollisionsWithPlayerAndEntities(const Player& player, const std::vector<std::shared_ptr<NpcEntity>>& entities);
    void publishCollisionBetweenEntitiesAndPlayer(const Player& player, const std::vector<std::shared_ptr<NpcEntity>>& entities);
    void publishCollisionsBetweenEntitiesAndMap(const std::vector<std::shared_ptr<NpcEntity>>& entities,
            const std::vector<std::shared_ptr<Collidable>>& collidables);

    bool collisionOccurred(const Collidable& collidable1, const Collidable& collidable2);
    bool playerVicinityCollisionOccurred(const Player& player, const Collidable& collidable);
};


#endif //NEWNEW_COLLISIONMANAGER_H
