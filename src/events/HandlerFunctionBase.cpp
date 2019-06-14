#include "../../includes/events/HandlerFunctionBase.h"

void HandlerFunctionBase::execute(Event* event) {
    call(event);
}