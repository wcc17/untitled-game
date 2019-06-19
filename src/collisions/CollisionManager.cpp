#include "../../includes/collisions/CollisionManager.h"
#include "../../includes/collisions/PlayerCollisionEvent.h"

void CollisionManager::initialize(std::shared_ptr<EventBus> eventBus) {
    this->eventBus = eventBus;
}

void CollisionManager::handleCollisions(const Player& player, const std::vector<std::shared_ptr<NpcEntity>>& entities,
                                        const std::vector<Collidable>& mapCollidables) {

    bool collisionOccurred = publishCollisionsWithPlayerAndEntities(player, entities);
    if(!collisionOccurred) {
        publishCollisionsWithPlayerAndMap(player, mapCollidables);
    }

    //TODO: these need to be implemented and with the assumption that one entity can't collide with more than one thing
//    publishCollisionsBetweenEntitiesAndEntities(entities, mapCollidables);
//    publishCollisionsBetweenEntitiesAndMap(entities, mapCollidables);

}

bool CollisionManager::publishCollisionsWithPlayerAndMap(const Player& player, const std::vector<Collidable>& collidables) {
    for(Collidable collidable : collidables) {
        if(collisionOccurred(player, collidable)) {
            eventBus->publish(new PlayerCollisionEvent(collidable));
            return true;
        }
    }
    return false;
}

bool CollisionManager::publishCollisionsWithPlayerAndEntities(const Player& player, const std::vector<std::shared_ptr<NpcEntity>>& entities) {
    for(std::shared_ptr<NpcEntity> npc : entities) {
        if(collisionOccurred(player, *npc)) {
            eventBus->publish(new PlayerCollisionEvent(*npc));
            return true;
        }
    }

    return false;
}

bool CollisionManager::collisionOccurred(const Collidable& collidable1, const Collidable& collidable2) {
    return ( (collidable1.getName() != collidable2.getName())
        && ( (collidable1.getBoundingBox().intersects(collidable2.getBoundingBox()) )));
}