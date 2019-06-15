#ifndef NEWNEW_COLLISIONMANAGER_H
#define NEWNEW_COLLISIONMANAGER_H

#include <vector>
#include "../events/EventBus.h"
#include "Collidable.h"

class CollisionManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void handleCollisions(std::vector<Collidable> entityCollidables, std::vector<Collidable> mapCollidables);

private:
    std::vector<std::pair<Collidable, Collidable>> getCollisions(std::vector<Collidable> entityCollidables,
            std::vector<Collidable> mapCollidables);
    void checkCollisionsBetweenEntitiesAndOthers(std::vector<Collidable>& entityCollidables,
                                                 std::vector<Collidable> otherCollidables,
                                                 std::vector<std::pair<Collidable, Collidable>>& collisions,
                                                 bool checkBetweenTwoEntities);
    bool collisionOccurred(Collidable collidable1, Collidable collidable2);
    bool collisionOccurredBetweenEntityAndEntity(Collidable collidable1, Collidable collidable2);
    bool isTypePartOfCollision(CollidableType type, std::pair<Collidable, Collidable> collision);

    std::shared_ptr<EventBus> eventBus;
};


#endif //NEWNEW_COLLISIONMANAGER_H
