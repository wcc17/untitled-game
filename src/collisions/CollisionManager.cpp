#include "../../includes/collisions/CollisionManager.h"

Logger CollisionManager::logger("CollisionManager");

void CollisionManager::initialize(std::shared_ptr<EventBus> eventBus) {
    this->eventBus = eventBus;
}

//TODO: does it really make sense to only handle one collision per frame? Or is it doing a bunch of extra work?
//TODO: consider referring to "collisions" as something else to differentiate it from vicinity collision
void CollisionManager::handleCollisions(Player& player,
                                        const std::vector<std::shared_ptr<NpcEntity>>& entities,
                                        const std::vector<std::shared_ptr<Collidable>>& mapCollidables) {

    handlePlayerCollisions(player, entities, mapCollidables);
    handleEntityCollisions(player, entities, mapCollidables);
}

void CollisionManager::handlePlayerCollisions(Player& player,
                                              const std::vector<std::shared_ptr<NpcEntity>>& entities,
                                              const std::vector<std::shared_ptr<Collidable>>& mapCollidables) {
    publishCollisionsWithPlayerAndEntities(player, entities);
    publishCollisionsWithPlayerAndMap(player, mapCollidables);
}

void CollisionManager::publishCollisionsWithPlayerAndMap(Player& player, const std::vector<std::shared_ptr<Collidable>>& collidables) {

    for(std::shared_ptr<Collidable> collidable : collidables) {
        if(collisionOccurred(player.getEntityCollidable(), *collidable)) {

            if(playerDoorCollisionOccurred(player, *collidable)) {
                eventBus->publish(new PlayerDoorCollisionEvent(*collidable));
            } else if(collidable->getType() != ObjectType::DOOR){
                eventBus->publish(new PlayerCollisionEvent(*collidable));
            }
        }

        if(playerVicinityCollisionOccurred(player, *collidable)) {
            eventBus->publish(new PlayerVicinityCollisionEvent(collidable));
        }
    }
}

void CollisionManager::publishCollisionsWithPlayerAndEntities(Player& player, const std::vector<std::shared_ptr<NpcEntity>>& entities) {

    for(std::shared_ptr<NpcEntity> npc : entities) {
        if(collisionOccurred(player.getEntityCollidable(), npc->getEntityCollidable())) {
            eventBus->publish(new PlayerCollisionEvent(npc->getEntityCollidable()));
        }

        if(playerVicinityCollisionOccurred(player, npc->getEntityCollidable())) {
            eventBus->publish(new PlayerVicinityCollisionEvent(std::make_shared<Collidable>(npc->getEntityCollidable())));
        }
    }
}

void CollisionManager::handleEntityCollisions(Player& player,
                                              const std::vector<std::shared_ptr<NpcEntity>>& entities,
                                              const std::vector<std::shared_ptr<Collidable>>& mapCollidables) {

    publishCollisionBetweenEntitiesAndPlayer(player, entities);
//    publishCollisionsBetweenEntitiesAndEntity(entities, hasEntityCollidedMap); //TODO: this isn't working right now. Entities can push each other out of the map. May have to approach differently
    publishCollisionsBetweenEntitiesAndMap(entities, mapCollidables);
}

void CollisionManager::publishCollisionBetweenEntitiesAndPlayer(Player& player,
        const std::vector<std::shared_ptr<NpcEntity>>& entities) {

    for(std::shared_ptr<NpcEntity> npc : entities) {
        if(collisionOccurred(npc->getEntityCollidable(), player.getEntityCollidable())) {
            eventBus->publish(new NpcCollisionEvent(*npc, player.getEntityCollidable()));
        }
    }

}

//void CollisionManager::publishCollisionsBetweenEntitiesAndEntity(const std::vector<std::shared_ptr<NpcEntity>>& entities, std::map<std::string, bool>& hasEntityCollidedMap) {
//    for(std::shared_ptr<NpcEntity> npc1 : entities) {
//        if(!hasEntityCollidedMap[npc1->getEntityCollidable().getName()]) {
//
//            for(std::shared_ptr<NpcEntity> npc2 : entities) {
//                if(npc1->getEntityCollidable().getName() != npc2->getEntityCollidable().getName()
//                    && !hasEntityCollidedMap[npc2->getEntityCollidable().getName()]
//                    && collisionOccurred(npc1->getEntityCollidable(), npc2->getEntityCollidable())) {
//
//                    hasEntityCollidedMap[npc1->getEntityCollidable().getName()] = true;
//                    hasEntityCollidedMap[npc2->getEntityCollidable().getName()] = true;
//                    eventBus->publish(new NpcCollisionEvent(*npc1, npc2->getEntityCollidable()));
//                }
//            }
//        }
//    }
//}

void CollisionManager::publishCollisionsBetweenEntitiesAndMap(const std::vector<std::shared_ptr<NpcEntity>>& entities,
        const std::vector<std::shared_ptr<Collidable>>& collidables) {

    for(std::shared_ptr<NpcEntity> npc : entities) {
        for(std::shared_ptr<Collidable> collidable : collidables) {
            if(collisionOccurred(npc->getEntityCollidable(), *collidable)) {
                eventBus->publish(new NpcCollisionEvent(*npc, *collidable));
            }
        }
    }
}

bool CollisionManager::collisionOccurred(const Collidable& collidable1, const Collidable& collidable2) {
    return ( (collidable1.getName() != collidable2.getName())
        && ( (collidable1.getBoundingBox().intersects(collidable2.getBoundingBox()) )));
}

bool CollisionManager::playerVicinityCollisionOccurred(Player& player, const Collidable& collidable) {
    const sf::FloatRect& playerVicinityBounds = player.getEntityCollidable().getVicinityBounds();
    return (playerVicinityBounds.intersects(collidable.getBoundingBox()));
}

//ensure player is actually inside the door
bool CollisionManager::playerDoorCollisionOccurred(Player& player, const Collidable& collidable) {
    if(collidable.getType() == ObjectType::DOOR) {
        const sf::FloatRect& playerBounds = player.getEntityCollidable().getBoundingBox();
        const sf::FloatRect& doorBounds = collidable.getBoundingBox();

        switch(player.getLastFacingDirection()) {
            case MoveDirection::DOWN:
            case MoveDirection::UP:
                if( (playerBounds.left >= doorBounds.left)
                    && ((playerBounds.left + playerBounds.width) <= (doorBounds.left + doorBounds.width))) {
                    return true;
                }
                break;
            case MoveDirection::RIGHT:
            case MoveDirection::LEFT:
                if( (playerBounds.top >= doorBounds.top)
                    && ((playerBounds.top + playerBounds.height) <= (doorBounds.top + doorBounds.height))) {
                    return true;
                }
                break;
            default:
                logger.logError("Should be looking at player's entityMovement's previous moving direction instead of its current direction.");
                return false;
        }
    }

    return false;
}