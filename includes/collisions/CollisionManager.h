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
#include "../../includes/events/event/PlayerDoorCollisionEvent.h"
#include "../../includes/events/event/AggressiveNpcCollisionEvent.h"

class CollisionManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void handleCollisions(Player& player,
            const std::vector<std::shared_ptr<NpcEntity>>& entities,
            const std::vector<std::shared_ptr<Collidable>>& mapCollidables);

private:
    std::shared_ptr<EventBus> eventBus;
    static Logger logger;

    void handlePlayerCollisions(Player& player, const std::vector<std::shared_ptr<NpcEntity>>& entities, const std::vector<std::shared_ptr<Collidable>>& mapCollidables);
    void publishCollisionsWithPlayerAndMap(Player& player, const std::vector<std::shared_ptr<Collidable>>& collidables);
    void publishCollisionsWithPlayerAndEntities(Player& player, const std::vector<std::shared_ptr<NpcEntity>>& entities);

    void handleEntityCollisions(Player& player, const std::vector<std::shared_ptr<NpcEntity>>& entities, const std::vector<std::shared_ptr<Collidable>>& mapCollidables);
    void publishCollisionsBetweenEntitiesAndEntity(const std::vector<std::shared_ptr<NpcEntity>>& entities);
    void publishCollisionsBetweenEntitiesAndMap(const std::vector<std::shared_ptr<NpcEntity>>& entities, const std::vector<std::shared_ptr<Collidable>>& collidables);
    void handleCollisionWithPlayerAndNpcEntity(Player& player, std::shared_ptr<NpcEntity> npc);
    void handleCollisionWithNpcAndNpc(std::shared_ptr<NpcEntity> npc1, std::shared_ptr<NpcEntity> npc2);

    static bool collisionOccurred(const Collidable& collidable1, const Collidable& collidable2);
    static bool playerVicinityCollisionOccurred(Player& player, const Collidable& collidable);
    static bool playerDoorCollisionOccurred(Player& player, const Collidable& collidable);
};


#endif //NEWNEW_COLLISIONMANAGER_H
