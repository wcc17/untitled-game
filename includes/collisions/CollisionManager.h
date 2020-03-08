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
#include "CollisionUtil.h"
#include "CollisionPublisher.h"

class CollisionManager {

public:
    CollisionManager();
    void initialize(std::shared_ptr<EventBus> eventBus);
    void initializeForScene(std::vector<std::shared_ptr<Collidable>> mapCollidables);
    void checkAllCollisions(const std::shared_ptr<Player>& player,
            const std::vector<std::shared_ptr<NpcEntity>>& entities);

private:
    CollisionPublisher collisionPublisher;
    std::vector<std::shared_ptr<Collidable>> mapCollidables;
    static Logger logger;

    void checkCollisionsWithPlayerAndMap(const std::shared_ptr<Player>& player);
    void checkCollisionsWithPlayerAndEntities(const std::shared_ptr<Player>& player, const std::vector<std::shared_ptr<NpcEntity>>& entities);
    void checkCollisionsBetweenEntitiesAndEntity(const std::vector<std::shared_ptr<NpcEntity>>& entities);
    void checkCollisionsBetweenEntitiesAndMap(const std::vector<std::shared_ptr<NpcEntity>>& entities);

    void handleCollisionWithPlayerAndNpcEntity(const std::shared_ptr<Player>& player, std::shared_ptr<NpcEntity> npc);
    void handleCollisionWithNpcAndNpc(const std::shared_ptr<NpcEntity> npc1, const std::shared_ptr<NpcEntity> npc2);
    void handleCollisionWithPlayerAndDoor(const std::shared_ptr<Player>& player, const Collidable& collidable);
    void handleCollisionWithPlayerAndMap(const std::shared_ptr<Player>& player, const std::shared_ptr<Collidable> collidable);
    void handleCollisionBetweenNpcEntityAndMap(const std::shared_ptr<NpcEntity> npc, const std::shared_ptr<Collidable> collidable);
    void handleCollisionWithPlayerVicinityAndNpcEntity(const std::shared_ptr<NpcEntity> npcEntity);
    void handleCollisionWithPlayerVicinityAndMap(const std::shared_ptr<Collidable> collidable);
};


#endif //NEWNEW_COLLISIONMANAGER_H
