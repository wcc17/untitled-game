#ifndef NEWNEW_EVENTBUS_H
#define NEWNEW_EVENTBUS_H

#include "MemberFunctionHandler.h"
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
        handlers = NULL;
    }

    template<class T, class EventType> void unsubscribe(T* instance, void (T::*memberFunction)(EventType *)) {
        HandlerList* handlers = subscribers[typeid(EventType)];
        if(handlers != nullptr) {

            std::list<HandlerFunctionBase*>::iterator it = handlers->begin();
            std::list<HandlerFunctionBase*>::iterator end = handlers->end();
            while (it != end) {
                MemberFunctionHandler<T, EventType>* handler = dynamic_cast<MemberFunctionHandler<T, EventType>*>(*it);

                if(handler == NULL) {
                    //NOTE: dynamic_cast returning null means that we tried to assign a class to the object that doesn't actually match what class it is. If thats the case here, we don't even need to check it because its definitely not the correct MemberFunction
                    ++it; //iterate normally, nothing to do here
                } else {
                    if(handler->getMemberFunction() == memberFunction) {
                        delete* it;
                        it = handlers->erase(it);
                    } else {
                        ++it;
                    }
                }
            }
        }

        handlers = NULL; //TODO: dangling pointer if not set to NULL?
    }

private:
    std::map<std::type_index, HandlerList*> subscribers;
};


#endif //NEWNEW_EVENTBUS_H
