#ifndef NEWNEW_COLLISIONMANAGER_H
#define NEWNEW_COLLISIONMANAGER_H

#include <vector>
#include "../level/collidable/Collidable.h"
#include "../events/EventBus.h"

class CollisionManager {
public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void handleCollisions(sf::FloatRect playerBounds, std::vector<Collidable> mapCollidables);

private:
    std::vector<Collidable> getCollisions(sf::FloatRect playerBounds, std::vector<Collidable> mapCollidables);
    void handleWallCollision();
    void handleDoorCollision();
    void handleSignCollision();
    void handlePlayerCollision();

    std::shared_ptr<EventBus> eventBus;
};


#endif //NEWNEW_COLLISIONMANAGER_H
