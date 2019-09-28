#ifndef NEWNEW_COLLISIONPUBLISHER_H
#define NEWNEW_COLLISIONPUBLISHER_H

#include "../../includes/events/event/PlayerCollisionEvent.h"
#include "../../includes/events/event/NpcCollisionEvent.h"
#include "../../includes/events/event/PlayerVicinityCollisionEvent.h"
#include "../../includes/events/event/PlayerDoorCollisionEvent.h"
#include "../entity/components/EntityCollidable.h"
#include "../events/EventBus.h"

class CollisionPublisher {

public:
    void initialize(const std::shared_ptr<EventBus> eventBus);
    void publishPlayerCollisionEvent(const sf::Vector2f& newPlayerPosition);
    void publishNpcCollisionEvent(
            const NpcEntity& npcEntity,
            const sf::Vector2f& newNpcPosition);
    void publishPlayerVicinityCollisionEvent(const std::shared_ptr<Collidable> collidable);
    void publishPlayerDoorCollisionEvent(const Collidable& collidable);

private:
    std::shared_ptr<EventBus> eventBus;

};


#endif //NEWNEW_COLLISIONPUBLISHER_H
