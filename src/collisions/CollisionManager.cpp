#include "../../includes/collisions/CollisionManager.h"

Logger CollisionManager::logger("CollisionManager");

CollisionManager::CollisionManager() : mapCollidables(std::vector<std::shared_ptr<Collidable>>()) { }

void CollisionManager::initialize(std::shared_ptr<EventBus> eventBus) {
    collisionPublisher.initialize(eventBus);
}

void CollisionManager::initializeForScene(std::vector<std::shared_ptr<Collidable>> mapCollidables) {
    this->mapCollidables = mapCollidables;
}

void CollisionManager::checkAllCollisions(const std::shared_ptr<Player>& player,
                                        const std::vector<std::shared_ptr<NpcEntity>>& entities) {

    //checkAllCollisions will go through all possible collisions
    //for each type of collision, we check if the collision occurred
    //if that particular check occurred, it will call a handleXCollision function
    //the handleXCollision functions all assume a collision occurred, will fix that collision, then publish an event saying the collision happened

    //player collisions
    checkCollisionsWithPlayerAndEntities(player, entities);
    checkCollisionsWithPlayerAndMap(player);

    //entity collisions
    checkCollisionsBetweenEntitiesAndEntity(entities);
    checkCollisionsBetweenEntitiesAndMap(entities);
}

void CollisionManager::checkCollisionsWithPlayerAndEntities(const std::shared_ptr<Player>& player, const std::vector<std::shared_ptr<NpcEntity>>& entities) {

    for(std::shared_ptr<NpcEntity> npc : entities) {
        EntityCollidable playerCollidable = player->getEntityCollidable();
        EntityCollidable npcCollidable = npc->getEntityCollidable();

        if(CollisionUtil::collisionOccurred(playerCollidable, npcCollidable)) {
            handleCollisionWithPlayerAndNpcEntity(player, npc);
        }

        if(CollisionUtil::playerVicinityCollisionOccurred(*player, npcCollidable)) {
            handleCollisionWithPlayerVicinityAndNpcEntity(npc);
        }
    }
}

void CollisionManager::checkCollisionsWithPlayerAndMap(const std::shared_ptr<Player>& player) {

    for(std::shared_ptr<Collidable> collidable : mapCollidables) {

        EntityCollidable playerCollidable = player->getEntityCollidable();
        if(CollisionUtil::collisionOccurred(playerCollidable, *collidable)) {

            if(CollisionUtil::playerDoorCollisionOccurred(*player, *collidable)) {
                handleCollisionWithPlayerAndDoor(player, *collidable);
            } else if(collidable->getType() != ObjectType::DOOR){
                handleCollisionWithPlayerAndMap(player, collidable);
            }
        }

        if(CollisionUtil::playerVicinityCollisionOccurred(*player, *collidable)) {
            handleCollisionWithPlayerVicinityAndMap(collidable);
        }
    }
}

void CollisionManager::checkCollisionsBetweenEntitiesAndEntity(const std::vector<std::shared_ptr<NpcEntity>>& entities) {
    for(std::shared_ptr<NpcEntity> npc1 : entities) {
        for(std::shared_ptr<NpcEntity> npc2 : entities) {

            EntityCollidable npc1Collidable = npc1->getEntityCollidable();
            EntityCollidable npc2Collidable = npc2->getEntityCollidable();

            if(npc1Collidable.getName() != npc2Collidable.getName()
               && CollisionUtil::collisionOccurred(npc1Collidable, npc2Collidable)) {
                handleCollisionWithNpcAndNpc(npc1, npc2);
            }
        }
    }
}

void CollisionManager::checkCollisionsBetweenEntitiesAndMap(const std::vector<std::shared_ptr<NpcEntity>>& entities) {

    for(std::shared_ptr<NpcEntity> npc : entities) {
        for(std::shared_ptr<Collidable> collidable : mapCollidables) {

            EntityCollidable entityCollidable = npc->getEntityCollidable();
            if(CollisionUtil::collisionOccurred(entityCollidable, *collidable)) {
                handleCollisionBetweenNpcEntityAndMap(npc, collidable);
            }
        }
    }
}

void CollisionManager::handleCollisionWithPlayerAndNpcEntity(const std::shared_ptr<Player>& player, const std::shared_ptr<NpcEntity> npc) {
    sf::Vector2f playerPosition;
    sf::Vector2f npcPosition;

    CollisionUtil::fixCollidablePositionAfterCollision(
            player->getEntityCollidable(),
            npc->getEntityCollidable(),
            sf::Vector2u(8, 8),
            playerPosition,
            npcPosition);

    if(!CollisionUtil::positionsAreEqual(playerPosition, player->getPosition())) {
        collisionPublisher.publishPlayerCollisionEvent(playerPosition);
    }

    if(!CollisionUtil::positionsAreEqual(npcPosition, npc->getPosition())) {
        collisionPublisher.publishNpcCollisionEvent(*npc, npcPosition);
    }

    collisionPublisher.publishPlayerAndNpcCollisionEvent(*npc);
}

void CollisionManager::handleCollisionWithNpcAndNpc(const std::shared_ptr<NpcEntity> npc1, const std::shared_ptr<NpcEntity> npc2) {
    sf::Vector2f npcPosition1;
    sf::Vector2f npcPosition2;

    CollisionUtil::fixCollidablePositionAfterCollision(
            npc1->getEntityCollidable(),
            npc2->getEntityCollidable(),
            sf::Vector2u(8, 8),
            npcPosition1,
            npcPosition2);

    if(!CollisionUtil::positionsAreEqual(npcPosition1, npc1->getPosition())) {
        collisionPublisher.publishNpcCollisionEvent(*npc1, npcPosition1);
    }

    if(!CollisionUtil::positionsAreEqual(npcPosition2, npc2->getPosition())) {
        collisionPublisher.publishNpcCollisionEvent(*npc2, npcPosition2);
    }
}


void CollisionManager::handleCollisionWithPlayerAndDoor(const std::shared_ptr<Player>& player, const Collidable& collidable) {
    collisionPublisher.publishPlayerDoorCollisionEvent(collidable);
}

void CollisionManager::handleCollisionWithPlayerAndMap(const std::shared_ptr<Player>& player, const std::shared_ptr<Collidable> collidable) {
    sf::Vector2f playerPosition;
    sf::Vector2f collidablePosition; //TODO: should I add a parameter to fixCollidablePositionAfterCollision to ignore these?

    CollisionUtil::fixCollidablePositionAfterCollision(
            player->getEntityCollidable(),
            *collidable,
            sf::Vector2u(8, 8),
            playerPosition,
            collidablePosition);
    collisionPublisher.publishPlayerCollisionEvent(playerPosition);
}

void CollisionManager::handleCollisionBetweenNpcEntityAndMap(const std::shared_ptr<NpcEntity> npc, const std::shared_ptr<Collidable> collidable) {
    sf::Vector2f npcPosition;
    sf::Vector2f collidablePosition; //TODO: should I add a parameter to fixCollidablePositionAfterCollision to ignore these?

    CollisionUtil::fixCollidablePositionAfterCollision(
            npc->getEntityCollidable(),
            *collidable,
            sf::Vector2u(8, 8),
            npcPosition,
            collidablePosition);
    collisionPublisher.publishNpcCollisionEvent(*npc, npcPosition);
}

void CollisionManager::handleCollisionWithPlayerVicinityAndNpcEntity(const std::shared_ptr<NpcEntity> npcEntity) {
    collisionPublisher.publishPlayerVicinityCollisionEvent(std::make_shared<Collidable>(npcEntity->getEntityCollidable()));
}

void CollisionManager::handleCollisionWithPlayerVicinityAndMap(const std::shared_ptr<Collidable> collidable) {
    collisionPublisher.publishPlayerVicinityCollisionEvent(collidable);
}