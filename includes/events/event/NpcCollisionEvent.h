#ifndef NEWNEW_NPCCOLLISIONEVENT_H
#define NEWNEW_NPCCOLLISIONEVENT_H

#include "../Event.h"
#include "../../collisions/Collidable.h"
#include "../../entity/npc/NpcEntity.h"

class NpcCollisionEvent : public Event {
public:
    NpcCollisionEvent(
            const NpcEntity& npc,
            const sf::Vector2f& newNpcPosition)
        : npc(npc), newNpcPosition(newNpcPosition) {}
    const NpcEntity& npc;
    const sf::Vector2f& newNpcPosition;
};


#endif //NEWNEW_NPCCOLLISIONEVENT_H
