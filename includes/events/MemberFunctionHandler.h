#ifndef NEWNEW_MEMBERFUNCTIONHANDLER_H
#define NEWNEW_MEMBERFUNCTIONHANDLER_H


#include "HandlerFunctionBase.h"

template<class T, class EventType> class MemberFunctionHandler : public HandlerFunctionBase {

public:
    typedef void (T::*MemberFunction)(EventType*);
    MemberFunctionHandler(T* instance, MemberFunction memberFunction) : instance{ instance }, memberFunction{ memberFunction } {};
    void call(Event* event) {
        // cast event to the correct type and call the member function
        (instance->*memberFunction)(static_cast<EventType*>(event));
    }

    MemberFunction getMemberFunction() {
        return this->memberFunction;
    }

private:
    T* instance;
    MemberFunction memberFunction;
};


#endif //NEWNEW_MEMBERFUNCTIONHANDLER_H
