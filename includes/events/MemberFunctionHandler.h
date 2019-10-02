#ifndef NEWNEW_MEMBERFUNCTIONHANDLER_H
#define NEWNEW_MEMBERFUNCTIONHANDLER_H


#include "HandlerFunctionBase.h"
#include <string>

template<class T, class EventType> class MemberFunctionHandler : public HandlerFunctionBase {

public:
    typedef void (T::*MemberFunction)(EventType*);

    MemberFunctionHandler(
            T* instance,
            MemberFunction memberFunction,
            std::string instanceClassName)
            : instance{ instance }, memberFunction{ memberFunction }, instanceClassName {instanceClassName} {};

    void call(Event* event) {
        // cast event to the correct type and call the member function
        (instance->*memberFunction)(static_cast<EventType*>(event));
    }

    MemberFunction getMemberFunction() {
        return this->memberFunction;
    }

    T* getInstance() {
        return this->instance;
    }

    std::string getInstanceClassName() {
        return this->instanceClassName;
    }

private:
    T* instance;
    MemberFunction memberFunction;
    std::string instanceClassName;
};


#endif //NEWNEW_MEMBERFUNCTIONHANDLER_H
