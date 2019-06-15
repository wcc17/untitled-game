#ifndef NEWNEW_CONTROLLERMOVEEVENT_H
#define NEWNEW_CONTROLLERMOVEEVENT_H


#include "../events/Event.h"
#include "MoveDirection.h"

class ControllerMoveEvent : public Event {
public:
    ControllerMoveEvent(MoveDirection direction) : direction(direction) {};
    MoveDirection direction;
};


#endif //NEWNEW_CONTROLLERMOVEEVENT_H
