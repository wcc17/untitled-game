#ifndef NEWNEW_EVENTBUS_H
#define NEWNEW_EVENTBUS_H

#include "../../includes/events/MemberFunctionHandler.h"
#include <list>
#include <typeindex>
#include <map>

//NOTE: code used from https://medium.com/@savas/nomad-game-engine-part-7-the-event-system-45a809ccb68f
typedef std::list<HandlerFunctionBase*> HandlerList;

class EventBus {
public:
    template<typename EventType> void publish(EventType* event) {
        HandlerList* handlers = subscribers[typeid(EventType)];

        if (handlers == nullptr) {
            return;
        }

        for (auto& handler : *handlers) {
            if(handler != nullptr) {
                handler->execute(event);
            }
        }

        delete event; //TODO: This _works_ but I think the whole event bus system can be done better with smart pointers
        event = NULL;
    }

    template<class T, class EventType> void subscribe(T* instance, void (T::*memberFunction)(EventType *)) {
        HandlerList* handlers = subscribers[typeid(EventType)];

        //perform first time initialization if necessary
        if (handlers == nullptr) {
            handlers = new HandlerList();
            subscribers[typeid(EventType)] = handlers;
        }

        handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
    }

    //TODO: surely I would need an "unsubscribe" for objects that need to be deleted/taken out of scope? I need to make sure this isn't sending to something that isn't available anymore (out of scope). This will live longer than most objects

private:
    std::map<std::type_index, HandlerList*> subscribers;
};


#endif //NEWNEW_EVENTBUS_H
