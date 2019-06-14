#ifndef NEWNEW_MOVEEVENT_H
#define NEWNEW_MOVEEVENT_H


#include "../events/Event.h"
#include "MoveDirection.h"

class MoveEvent : public Event {
public:
    MoveEvent(MoveDirection direction): direction(direction) {};
    MoveDirection direction;
};


#endif //NEWNEW_MOVEEVENT_H
