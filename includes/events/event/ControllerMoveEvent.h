#ifndef NEWNEW_CONTROLLERMOVEEVENT_H
#define NEWNEW_CONTROLLERMOVEEVENT_H


#include "../Event.h"
#include "../../controller/MoveDirection.h"

class ControllerMoveEvent : public Event {
public:
    ControllerMoveEvent(MoveDirection direction) : direction(direction) {};
    MoveDirection direction;
};


#endif //NEWNEW_CONTROLLERMOVEEVENT_H
