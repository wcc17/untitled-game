#include "../../../includes/entity/character/MovableEntity.h"

void MovableEntity::initialize(float moveSpeed) {
    this->moveSpeed = moveSpeed;
    this->state = STATE_STANDING;
}

void MovableEntity::update(sf::Time deltaTime) {
}

void MovableEntity::move(sf::Time deltaTime, MoveDirection direction, sf::Vector2u mapTileSize, sf::Vector2u mapSizeInPixels) {
    //TODO: should I re-call this method if the state changes or just wait until the next frame?
    //TODO: the state machine idea would be to call state->onMoveEvent(this, direction) for each state. wouldn't have to switch on state anymore

    resetMovement();

    switch(state) {
        case STATE_STANDING:
            printf("standing\n");
            handleStandingState(direction);
            break;
        case STATE_MOVING:
            printf("moving\n");
            handleMovingState(direction, deltaTime, mapTileSize, mapSizeInPixels);
            break;
        case STATE_MOVING_TO_GOAL:
            printf("moving to goal\n");
            handleMovingToGoalState(direction, deltaTime, mapTileSize, mapSizeInPixels);
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

    //now actually move the sprite
    Sprite::move(movement * deltaTime.asSeconds());
}

void MovableEntity::handleStandingState(MoveDirection direction) {
    currentDirection = direction;

    if(direction != MoveDirection::NONE) {  //if movement controls were pressed
        //TODO: calculate new movement goal
        state = STATE_MOVING; //if we're given a direction, start moving
        setRegularMovement();
    }
}

void MovableEntity::handleMovingState(MoveDirection direction, sf::Time deltaTime, sf::Vector2u mapTileSize, sf::Vector2u mapSizeInPixels) {
    currentDirection = direction;
    if(direction == MoveDirection::NONE) {

        if(movementGoalReached(deltaTime, mapTileSize, mapSizeInPixels)) {
            state = STATE_STANDING;
        } else {
            state = STATE_MOVING_TO_GOAL;
            currentDirection = previousDirection;
            setGoalLimitedMovement(deltaTime, mapTileSize, mapSizeInPixels);
        }
    } else {
        state = STATE_MOVING; //just keep moving
        setRegularMovement();
    }
}

void MovableEntity::handleMovingToGoalState(MoveDirection direction, sf::Time deltaTime, sf::Vector2u mapTileSize, sf::Vector2u mapSizeInPixels) {
    currentDirection = direction;

    if(movementGoalReached(deltaTime, mapTileSize, mapSizeInPixels)) {

        //decide whether we should allow moving in a different direction or not
        if(direction == MoveDirection::NONE) {
            state = STATE_STANDING;
        } else {
            state = STATE_MOVING;
            setRegularMovement();
        }
    } else {
        //if we haven't reached the goal, don't change the state and keep moving
        currentDirection = previousDirection;
//        setRegularMovement();
        setGoalLimitedMovement(deltaTime, mapTileSize, mapSizeInPixels);
    }

}

bool MovableEntity::movementGoalReached(sf::Time deltaTime, sf::Vector2u mapTileSize, sf::Vector2u mapSizeInPixels) {
    int position = 0;
    int tileSize = 0;
    switch(previousDirection) {
        case MoveDirection::UP:
        case MoveDirection::DOWN:
            position = getPosition().y;
            tileSize = mapTileSize.y;
            break;
        case MoveDirection::LEFT:
        case MoveDirection::RIGHT:
            position = getPosition().x;
            tileSize = mapTileSize.x;
            break;
        default:
            printf("this should not be happening\n");
            return true;
    }

    return (position % tileSize == 0); //if tileSize is a multiple of position, then our goal is reached
}

void MovableEntity::setGoalLimitedMovement(sf::Time deltaTime, sf::Vector2u mapTileSize, sf::Vector2u mapSizeInPixels) {
    //TODO: this is repeated exactly in movementGoalReached. do something about it
    int position = 0;
    int tileSize = 0;
    switch(currentDirection) {
        case MoveDirection::UP:
        case MoveDirection::DOWN:
            position = getPosition().y;
            tileSize = mapTileSize.y;
            break;
        case MoveDirection::LEFT:
        case MoveDirection::RIGHT:
            position = getPosition().x;
            tileSize = mapTileSize.x;
            break;
        default:
            return;
    }

    int goal = position + (tileSize - position % tileSize);

    sf::Vector2f move = movement;
    //TODO: this is repeated exactly in setRegularMovement, do smoething about it
    switch(currentDirection) {
        case MoveDirection::UP:
            move.y -= moveSpeed;
            break;
        case MoveDirection::LEFT:
            move.x -= moveSpeed;
            break;
        case MoveDirection::DOWN:
            move.y += moveSpeed;
            break;
        case MoveDirection::RIGHT:
            move.x += moveSpeed;
            break;
        default:
            printf("this should not be happening\n");
            return;
    }
    move *= deltaTime.asSeconds();


    //TOOD: this is not good, do something about it
    float moveXOrY = 0;
    switch(currentDirection) {
        case MoveDirection::UP:
        case MoveDirection::DOWN:
            moveXOrY = move.y;
            break;
        case MoveDirection::LEFT:
        case MoveDirection::RIGHT:
            moveXOrY = move.x;
            break;
        default:
            printf("this should not be happening\n");
            return;
    }

    float moveSpeedtoUse = 0;
    if((position + moveXOrY) > goal) {
        float newMovementSpeed = (goal - position); //NOTE: this is called "speed", but its what we want to multiply deltaTime by to get a number that puts us exactly at the move goal
        moveSpeedtoUse = newMovementSpeed / deltaTime.asSeconds();
    } else {
        moveSpeedtoUse += moveSpeed;
    }

    //TODO: this should be setRegularMovement that takes a movement parameter
    switch(currentDirection) {
        case MoveDirection::UP:
            movement.y -= moveSpeedtoUse;
            break;
        case MoveDirection::LEFT:
            movement.x -= moveSpeedtoUse;
            break;
        case MoveDirection::DOWN:
            movement.y += moveSpeedtoUse;
            break;
        case MoveDirection::RIGHT:
            movement.x += moveSpeedtoUse;
            break;
        default:
            printf("this should not be happening\n");
            break;
    }
}

void MovableEntity::setRegularMovement() {

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
            printf("this should not be happening\n");
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