#ifndef NEWNEW_NPCCOLLISIONEVENT_H
#define NEWNEW_NPCCOLLISIONEVENT_H

#include "../Event.h"
#include "../../collisions/Collidable.h"
#include "../../entity/character/NpcEntity.h"

class NpcCollisionEvent : public Event {
public:
    NpcCollisionEvent(NpcEntity& npc, const Collidable& collidedWith): npc(npc), collidedWith(collidedWith) {}
    const Collidable& collidedWith;
    NpcEntity& npc;
};


#endif //NEWNEW_NPCCOLLISIONEVENT_H
