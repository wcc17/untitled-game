#include "../../includes/collisions/CollisionManager.h"
#include "../../includes/collisions/PlayerCollisionEvent.h"

const bool CHECK_BETWEEN_TWO_ENTITIES = true;

void CollisionManager::initialize(std::shared_ptr<EventBus> eventBus) {
    this->eventBus = eventBus;
}

void CollisionManager::handleCollisions(Player player, std::vector<NpcEntity*> entities,
        std::vector<Collidable> mapCollidables) {

    bool collisionOccurred = publishCollisionsWithPlayerAndEntities(player, entities);
    if(!collisionOccurred) {
        publishCollisionsWithPlayerAndMap(player, mapCollidables);
    }

    //TODO: these need to be implemented and with the assumption that one entity can't collide with more than one thing
//    publishCollisionsBetweenEntitiesAndEntities(entities, mapCollidables);
//    publishCollisionsBetweenEntitiesAndMap(entities, mapCollidables);

}

bool CollisionManager::publishCollisionsWithPlayerAndMap(Player player, std::vector<Collidable> collidables) {
    for(Collidable collidable : collidables) {
        if(collisionOccurred(player, collidable)) {
            eventBus->publish(new PlayerCollisionEvent(std::make_pair(player, collidable)));
            return true;
        }
    }
    return false;
}

bool CollisionManager::publishCollisionsWithPlayerAndEntities(Player player, std::vector<NpcEntity*> entities) {
    for(NpcEntity* npc : entities) {
        if(collisionOccurred(player, *npc)) {
            eventBus->publish(new PlayerCollisionEvent(std::make_pair(player, *npc)));
            return true;
        }
    }

    return false;
}

bool CollisionManager::collisionOccurred(Collidable collidable1, Collidable collidable2) {
    return ( (collidable1.getName() != collidable2.getName())
        && ( (collidable1.getBoundingBox().intersects(collidable2.getBoundingBox()) )));
}