#include "../../includes/collisions/CollisionManager.h"
#include "../../includes/collisions/PlayerCollisionEvent.h"

const bool CHECK_BETWEEN_TWO_ENTITIES = true;

void CollisionManager::initialize(std::shared_ptr<EventBus> eventBus) {
    this->eventBus = eventBus;
}

void CollisionManager::handleCollisions(std::vector<Collidable> entityCollidables,
        std::vector<Collidable> mapCollidables) {

    std::vector<std::pair<Collidable, Collidable>> collisions = getCollisions(entityCollidables, mapCollidables);
    for(std::pair<Collidable, Collidable> collision : collisions) {
        if (isTypePartOfCollision(CollidableType::PLAYER, collision)) {
            eventBus->publish(new PlayerCollisionEvent(collision));
        }

        if (isTypePartOfCollision(CollidableType::NPC, collision)) {
            //TODO: implement once NPCs are in the game
        }
    }
}

std::vector<std::pair<Collidable, Collidable>> CollisionManager::getCollisions(std::vector<Collidable> entityCollidables,
        std::vector<Collidable> mapCollidables) {

    //NOTE: entities can collide with other entities, but map collidables will never collide with another map
    std::vector<std::pair<Collidable, Collidable>> collisions;
    checkCollisionsBetweenEntitiesAndOthers(entityCollidables, entityCollidables, collisions, CHECK_BETWEEN_TWO_ENTITIES);
    checkCollisionsBetweenEntitiesAndOthers(entityCollidables, mapCollidables, collisions, !CHECK_BETWEEN_TWO_ENTITIES);
    return collisions;
}

void CollisionManager::checkCollisionsBetweenEntitiesAndOthers(std::vector<Collidable>& entityCollidables, std::vector<Collidable> otherCollidables,
        std::vector<std::pair<Collidable, Collidable>>& collisions, bool checkBetweenTwoEntities) {

    //NOTE: this is assuming that an entity could only ever collide with one other thing (entity or object or whatever). It will handle one collision, fix it, and the next (if thats even possible) will be fixed next frame
    for (std::vector<Collidable>::iterator it = entityCollidables.begin(); it != entityCollidables.end();) {
        bool entityRemoved = false;

        for(Collidable collidedWith : otherCollidables) {

            //check if collision actually occurred
            bool collisionDidOccur = false;
            if(checkBetweenTwoEntities) {
                collisionDidOccur = collisionOccurredBetweenEntityAndEntity(*it, collidedWith);
            } else {
                collisionDidOccur = collisionOccurred(*it, collidedWith);
            }

            //if collision occurred, remove entity from entityCollidables
            if(collisionDidOccur) {
                collisions.push_back(std::make_pair(*it, collidedWith));

                it = entityCollidables.erase(it);
                entityRemoved = true;
                break;
            }
        }

        //only increment if nothing was removed from outer vector. erase gives a new it value anyway
        if(!entityRemoved) {
            ++it;
        }
    }
}

bool CollisionManager::collisionOccurred(Collidable collidable1, Collidable collidable2) {
    return (collidable1.getBoundingBox().intersects(collidable2.getBoundingBox()));
}

bool CollisionManager::collisionOccurredBetweenEntityAndEntity(Collidable collidable1, Collidable collidable2) {
    return ( (collidable1.getName() != collidable2.getName()) && (collisionOccurred(collidable1, collidable2)) );
}

bool CollisionManager::isTypePartOfCollision(CollidableType type, std::pair<Collidable, Collidable> collision) {
    return (collision.first.getType() == type || collision.second.getType() == type);
}