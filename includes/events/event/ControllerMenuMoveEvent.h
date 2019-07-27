#ifndef NEWNEW_CONTROLLERMENUMOVEEVENT_H
#define NEWNEW_CONTROLLERMENUMOVEEVENT_H

#include "../Event.h"
#include "../../controller/MoveDirection.h"

class ControllerMenuMoveEvent : public Event {
public:
    ControllerMenuMoveEvent(MoveDirection direction) : direction(direction) {};
    MoveDirection direction;
};

#endif //NEWNEW_CONTROLLERMENUMOVEEVENT_H
