#ifndef NEWNEW_PLAYERANDNPCCOLLISIONEVENT_H
#define NEWNEW_PLAYERANDNPCCOLLISIONEVENT_H

#include "../Event.h"
#include "../../collisions/Collidable.h"
#include "../../entity/npc/NpcEntity.h"

class PlayerAndNpcCollisionEvent : public Event {
public:
    PlayerAndNpcCollisionEvent(const NpcEntity& npc) : npc(npc) {}
    const NpcEntity& npc;
};

#endif //NEWNEW_PLAYERANDNPCCOLLISIONEVENT_H
