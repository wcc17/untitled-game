#include "../../includes/collisions/CollisionPublisher.h"

void CollisionPublisher::initialize(std::shared_ptr<EventBus> eventBus) {
    this->eventBus = eventBus;
}

void CollisionPublisher::publishPlayerCollisionEvent(const sf::Vector2f& newPlayerPosition) {
    eventBus->publish(new PlayerCollisionEvent(newPlayerPosition));
}

void CollisionPublisher::publishNpcCollisionEvent(
        const NpcEntity& npcEntity,
        const sf::Vector2f& newNpcPosition) {
    eventBus->publish(new NpcCollisionEvent(npcEntity, newNpcPosition));
}

void CollisionPublisher::publishPlayerVicinityCollisionEvent(const std::shared_ptr<Collidable> collidable) {
    eventBus->publish(new PlayerVicinityCollisionEvent(collidable));
}

void CollisionPublisher::publishPlayerDoorCollisionEvent(const Collidable& collidable) {
    eventBus->publish(new PlayerDoorCollisionEvent(collidable));
}

void CollisionPublisher::publishPlayerAndNpcCollisionEvent(const NpcEntity& npc) {
    eventBus->publish(new PlayerAndNpcCollisionEvent(npc));
}