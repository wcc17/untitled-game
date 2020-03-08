#include "../../includes/scene/SceneStateHandler.h"

SceneState SceneStateHandler::getNextState(SceneState currentState) {
    //transition in > change scene > scene > transition out > change scene > transition in > ......
    switch(currentState) {
        case STATE_SCENE:
            return STATE_TRANSITION_SCENE_OUT;
        case STATE_TRANSITION_SCENE_OUT:
            return STATE_CHANGING_SCENE;
        case STATE_CHANGING_SCENE:
            return STATE_SKIP_FRAME;
        case STATE_SKIP_FRAME:
            return STATE_TRANSITION_SCENE_IN;
        case STATE_TRANSITION_SCENE_IN:
            return STATE_SCENE;
        default:
            return currentState;
    }
}
