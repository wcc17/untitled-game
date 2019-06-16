#include "../../../includes/entity/character/MovableEntity.h"

void MovableEntity::initialize(float moveSpeed) {
    this->moveSpeed = moveSpeed;
    this->state = STATE_STANDING;
}

void MovableEntity::update(sf::Time deltaTime) {
}

void MovableEntity::move(MoveDirection direction) {
    //TODO: should I re-call this method if the state changes or just wait until the next frame?
    //TODO: the state machine idea would be to call state->onMoveEvent(this, direction) for each state. wouldn't have to switch on state anymore

    resetMovement();

    switch(state) {
        case STATE_STANDING:
            handleStandingState(direction);
            break;
        case STATE_MOVING:
            handleMovingState(direction);
            break;
        case STATE_MOVING_TO_GOAL:
            handleMovingToGoalState(direction);
            break;
    }

    /**
     * Player starts out standing
     * As a movement button is being pressed:
     *  1. the state changes to "STATE_MOVING"
     *  2. a goal is set depending on the direction (the next closest tile)
     *  3. the player moves to that goal
     * If no movement button is being pressed
     *  1. if no goal has been reached, the state changes to "STATE_MOVING_TO_GOAL"
     *      a. Entity will keep moving in the most previous direction until goal is reached
     *  2. if we're at a goal, the state changes to "STATE_STANDING"
     *      a. previous direction is cleared, we don't care about it anymore
     *
     *  Player > Character Entity > AnimatedEntity, Collidable
     *  Character Entity has state?
     *
     *  Going to try with current configuration for now. I don't think the states will be that complex? The player can't really do more than one thing at a time
     *
     *  Should probably move all PlayerManager movement stuff into MovableEntity and then set the view from the player rather than setting the player position from the view.
     *  Because NPC will basically do the same things movement wise as the player
     */
}

void MovableEntity::handleStandingState(MoveDirection direction) {
    currentDirection = direction;

    if(direction == MoveDirection::NONE) {  //if no movement controls were pressed
        if(state == STATE_MOVING_TO_GOAL) { //if we're still moving to a goal
            currentDirection = previousDirection; //go toward that previous goal
            setMovementForCurrentDirection();
        } else {
            //if the player is standing and no direction is given, don't do anything
        }
    } else {
        //TODO: calculate new movement goal
        state = STATE_MOVING; //if we're given a direction, start moving
        setMovementForCurrentDirection();
    }
}

void MovableEntity::handleMovingState(MoveDirection direction) {
    currentDirection = direction;
    if(direction == MoveDirection::NONE) {
        //TODO: here we decide if we haven't reached the goal yet
        bool haveReachedGoal = true;
        if(haveReachedGoal) {
            state = STATE_STANDING;
        } else {
            state = STATE_MOVING_TO_GOAL;
            currentDirection = previousDirection;
        }
    } else {
        //TODO: calculate new movement goal. should this be calculated in setMovementForCurrentDirection?
        state = STATE_MOVING; //just keep moving
        setMovementForCurrentDirection();
    }
}

void MovableEntity::handleMovingToGoalState(MoveDirection direction) {
    currentDirection = direction;
    
    //TODO: here we decide if we haven't reached the goal yet
    bool haveReachedGoal = true;
    if(haveReachedGoal) {

        //decide whether we should allow moving in a different direction or not
        if(direction == MoveDirection::NONE) {
            state = STATE_STANDING;
        } else {
            state = STATE_MOVING;
            //TODO: calculate new movement goal. should this be calculated in setMovementForCurrentDirection?
            setMovementForCurrentDirection();
        }
    } else {
        //if we haven't reached the goal, don't change the state and keep moving
        currentDirection = previousDirection;
        setMovementForCurrentDirection();
    }

}

void MovableEntity::setMovementForCurrentDirection() {

    switch(currentDirection) {
        case MoveDirection::UP:
            movement.y -= moveSpeed;
            break;
        case MoveDirection::LEFT:
            movement.x -= moveSpeed;
            break;
        case MoveDirection::DOWN:
            movement.y += moveSpeed;
            break;
        case MoveDirection::RIGHT:
            movement.x += moveSpeed;
            break;
        default:
            break;
    }

    previousDirection = currentDirection; //only saving previous after the movement is set in stone
}

void MovableEntity::resetMovement() {
    movement.x = 0;
    movement.y = 0;
}

sf::Vector2f MovableEntity::getMovement() {
    return this->movement;
}