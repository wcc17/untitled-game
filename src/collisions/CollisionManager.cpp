#include "../../includes/collisions/CollisionManager.h"

void CollisionManager::initialize(std::shared_ptr<EventBus> eventBus) {
    this->eventBus = eventBus;
}

//TODO: consider referring to "collisions" as something else to differentiate it from vicinity collision
void CollisionManager::handleCollisions(const Player& player,
                                        const std::vector<std::shared_ptr<NpcEntity>>& entities,
                                        const std::vector<std::shared_ptr<Collidable>>& mapCollidables) {

    handlePlayerCollisions(player, entities, mapCollidables);
    handleEntityCollisions(player, entities, mapCollidables);
}

void CollisionManager::handlePlayerCollisions(const Player& player,
                                              const std::vector<std::shared_ptr<NpcEntity>>& entities,
                                              const std::vector<std::shared_ptr<Collidable>>& mapCollidables) {
    bool playerCollisionOccurred = publishCollisionsWithPlayerAndEntities(player, entities);
    if(!playerCollisionOccurred) {
        publishCollisionsWithPlayerAndMap(player, mapCollidables);
    }
}

bool CollisionManager::publishCollisionsWithPlayerAndMap(const Player& player, const std::vector<std::shared_ptr<Collidable>>& collidables) {
    //NOTE: only want to track a single hard collision since player can only move in one direction, can have many vicinity collisions
    bool collisionAlreadyOccurred = false;

    for(std::shared_ptr<Collidable> collidable : collidables) {
        if(!collisionAlreadyOccurred && collisionOccurred(player, *collidable)) {
            collisionAlreadyOccurred = true;
            eventBus->publish(new PlayerCollisionEvent(*collidable));
        }

        if(playerVicinityCollisionOccurred(player, *collidable)) {
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
            eventBus->publish(new PlayerVicinityCollisionEvent(npc));
        }
    }

    return collisionAlreadyOccurred;
}

void CollisionManager::handleEntityCollisions(const Player& player,
                                              const std::vector<std::shared_ptr<NpcEntity>>& entities,
                                              const std::vector<std::shared_ptr<Collidable>>& mapCollidables) {
    std::map<std::string, bool> hasEntityCollidedMap;
    initializeEntityCollidedMap(entities, hasEntityCollidedMap);

    publishCollisionBetweenEntitiesAndPlayer(player, entities, hasEntityCollidedMap);
    publishCollisionsBetweenEntitiesAndMap(entities, mapCollidables, hasEntityCollidedMap);
//    publishCollisionsBetweenEntitiesAndEntities(entities); //TODO: skipping this for now until entities can actually move in the same area (boundary) as one another. Should come before map collidables though?
}

void CollisionManager::initializeEntityCollidedMap(const std::vector<std::shared_ptr<NpcEntity>>& entities, std::map<std::string, bool>& hasEntityCollidedMap) {
    for(std::shared_ptr<NpcEntity> npcEntity : entities) {
        hasEntityCollidedMap.insert(std::make_pair(npcEntity->getName(), false));
    }
}

void CollisionManager::publishCollisionBetweenEntitiesAndPlayer(const Player& player,
        const std::vector<std::shared_ptr<NpcEntity>>& entities, std::map<std::string, bool>& hasEntityCollidedMap) {

    for(std::shared_ptr<NpcEntity> npc : entities) {
        if(!hasEntityCollidedMap[npc->getName()] && collisionOccurred(*npc, player)) {
            hasEntityCollidedMap[npc->getName()] = true;
            eventBus->publish(new NpcCollisionEvent(*npc, player));
        }
    }

}

void CollisionManager::publishCollisionsBetweenEntitiesAndMap(const std::vector<std::shared_ptr<NpcEntity>>& entities,
        const std::vector<std::shared_ptr<Collidable>>& collidables, std::map<std::string, bool>& hasEntityCollidedMap) {

    for(std::shared_ptr<NpcEntity> npc : entities) {
        for(std::shared_ptr<Collidable> collidable : collidables) {
            if(!hasEntityCollidedMap[npc->getName()] && collisionOccurred(*npc, *collidable)) {
                hasEntityCollidedMap[npc->getName()] = true;
                eventBus->publish(new NpcCollisionEvent(*npc, *collidable));
            }
        }
    }
}

bool CollisionManager::collisionOccurred(const Collidable& collidable1, const Collidable& collidable2) {
    return ( (collidable1.getName() != collidable2.getName())
        && ( (collidable1.getBoundingBox().intersects(collidable2.getBoundingBox()) )));
}

bool CollisionManager::playerVicinityCollisionOccurred(const Player& player, const Collidable& collidable) {
    return (player.getVicinityBounds().intersects(collidable.getBoundingBox()));
}