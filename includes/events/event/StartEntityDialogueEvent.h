#ifndef NEWNEW_STARTENTITYDIALOGUEEVENT_H
#define NEWNEW_STARTENTITYDIALOGUEEVENT_H

#include "../Event.h"

class StartEntityDialogueEvent : public Event {
public:
    StartEntityDialogueEvent(std::string npcName, MoveDirection playerFacingDirection): npcName(npcName), playerFacingDirection(playerFacingDirection) {}
    std::string npcName;
    MoveDirection playerFacingDirection;
};

#endif //NEWNEW_STARTENTITYDIALOGUEEVENT_H
