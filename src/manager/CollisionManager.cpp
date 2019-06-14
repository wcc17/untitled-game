#include "../../includes/manager/CollisionManager.h"
#include "../../includes/manager/CollisionEvent.h"

void CollisionManager::initialize(std::shared_ptr<EventBus> eventBus) {
    this->eventBus = eventBus;
}

void CollisionManager::handleCollisions(sf::FloatRect playerBounds, std::vector<Collidable> mapCollidables) {
    std::vector<Collidable> collisions = getCollisions(playerBounds, mapCollidables);

    //TODO: eventually need to consider that these collisions will happen to more than just a player. getCollisions will have to return pairs of Collidables
    for(Collidable collidable : collisions) {
        //TODO: this won't always be Player on map collisions
        eventBus->publish(new CollisionEvent(collidable.getType(), playerBounds, collidable.getBoundingBox()));
    }
}

//TODO: only passing player bounds for now, but will eventually want anything that could collide with something (so probably a vector of rects)
std::vector<Collidable> CollisionManager::getCollisions(sf::FloatRect playerBounds, std::vector<Collidable> mapCollidables) {
    std::vector<Collidable> collided;
    for(Collidable collidable : mapCollidables) {
        if(collidable.getBoundingBox().intersects(playerBounds)) {
            collided.push_back(collidable);
        }
    }

    return collided;
}

void CollisionManager::handleWallCollision() {
    // printf("colliding with a wall\n");
    handlePlayerCollision();
}

void CollisionManager::handleDoorCollision() {
    // printf("colliding with a door\n");
}

void CollisionManager::handleSignCollision() {
    // printf("colliding with a sign\n");
    handlePlayerCollision();
}

void CollisionManager::handlePlayerCollision() {
//    viewManager.undoMovement();
//    player.updatePlayerPosition(viewManager.getViewPosition());
}