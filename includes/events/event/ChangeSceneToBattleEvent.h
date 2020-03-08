#ifndef NEWNEW_CHANGESCENETOBATTLEEVENT_H
#define NEWNEW_CHANGESCENETOBATTLEEVENT_H

#include "../Event.h"
#include "../../entity/npc/NpcEntity.h"

class ChangeSceneToBattleEvent : public Event {
public:
    ChangeSceneToBattleEvent(const NpcEntity& npcEntity): npcEntity(npcEntity) {}
    const NpcEntity& npcEntity;
};

#endif //NEWNEW_CHANGESCENETOBATTLEEVENT_H
