#ifndef NEWNEW_COLLISIONMANAGER_H
#define NEWNEW_COLLISIONMANAGER_H

#include <vector>
#include "../events/EventBus.h"
#include "Collidable.h"
#include "../entity/character/NpcEntity.h"
#include "../entity/player/Player.h"

class CollisionManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void handleCollisions(Player player, std::vector<NpcEntity*> entities, std::vector<Collidable> mapCollidables);

private:
    bool publishCollisionsWithPlayerAndEntities(Player player, std::vector<NpcEntity*> entities);
    bool publishCollisionsWithPlayerAndMap(Player player, std::vector<Collidable> collidables);
    bool collisionOccurred(Collidable collidable1, Collidable collidable2);

    std::shared_ptr<EventBus> eventBus;
};


#endif //NEWNEW_COLLISIONMANAGER_H
