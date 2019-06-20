#include "../../includes/collisions/CollisionManager.h"

void CollisionManager::initialize(std::shared_ptr<EventBus> eventBus) {
    this->eventBus = eventBus;
}

//TODO: consider referring to "collisions" as something else to differentiate it from vicinity collision
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
    //NOTE: only want to track a single hard collision since player can only move in one direction, can have many vicinity collisions
    bool collisionAlreadyOccurred = false;

    for(Collidable collidable : collidables) {
        if(!collisionAlreadyOccurred && collisionOccurred(player, collidable)) {
            collisionAlreadyOccurred = true;
            eventBus->publish(new PlayerCollisionEvent(collidable));
        }

        if(playerVicinityCollisionOccurred(player, collidable)) {
            eventBus->publish(new PlayerVicinityCollisionEvent(collidable));
        }
    }

    return collisionAlreadyOccurred;
}

bool CollisionManager::publishCollisionsWithPlayerAndEntities(const Player& player, const std::vector<std::shared_ptr<NpcEntity>>& entities) {
    bool collisionAlreadyOccurred = false;

    for(std::shared_ptr<NpcEntity> npc : entities) {
        if(!collisionAlreadyOccurred && collisionOccurred(player, *npc)) {
            collisionAlreadyOccurred = true;
            eventBus->publish(new PlayerCollisionEvent(*npc));
        }

        if(playerVicinityCollisionOccurred(player, *npc)) {
            eventBus->publish(new PlayerVicinityCollisionEvent(*npc));
        }
    }

    return collisionAlreadyOccurred;
}

bool CollisionManager::collisionOccurred(const Collidable& collidable1, const Collidable& collidable2) {
    return ( (collidable1.getName() != collidable2.getName())
        && ( (collidable1.getBoundingBox().intersects(collidable2.getBoundingBox()) )));
}

bool CollisionManager::playerVicinityCollisionOccurred(const Player& player, const Collidable& collidable) {
    return (player.getVicinityBounds().intersects(collidable.getBoundingBox()));
}