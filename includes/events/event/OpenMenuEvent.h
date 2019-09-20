#ifndef NEWNEW_OPENMENUEVENT_H
#define NEWNEW_OPENMENUEVENT_H

#include "../Event.h"

class OpenMenuEvent : public Event {
public:
    OpenMenuEvent(UIComponentType menuToOpen) {
        this->menuToOpen = menuToOpen;
    }

    UIComponentType getMenuToOpen() {
        return this->menuToOpen;
    }
private:
    UIComponentType menuToOpen = UIComponentType::NO_COMPONENT_TYPE;

};

#endif //NEWNEW_OPENMENUEVENT_H
