#ifndef NEWNEW_AGGRESSIVENPCCOLLISIONEVENT_H
#define NEWNEW_AGGRESSIVENPCCOLLISIONEVENT_H

#include "../Event.h"
#include "../../entity/npc/NpcEntity.h"

class AggressiveNpcCollisionEvent : public Event {
public:
    AggressiveNpcCollisionEvent(NpcEntity& npc): npc(npc) {}
    NpcEntity& npc;
};

#endif //NEWNEW_AGGRESSIVENPCCOLLISIONEVENT_H
