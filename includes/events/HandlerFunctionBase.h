#ifndef NEWNEW_HANDLERFUNCTIONBASE_H
#define NEWNEW_HANDLERFUNCTIONBASE_H


#include "Event.h"

class HandlerFunctionBase {
public:
    void execute(Event* event);
    virtual ~HandlerFunctionBase() {};
private:
    virtual void call(Event* event) = 0;
};


#endif //NEWNEW_HANDLERFUNCTIONBASE_H
