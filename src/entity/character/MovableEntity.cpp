#include "../../../includes/entity/character/MovableEntity.h"

void MovableEntity::initialize(float moveSpeed) {
    this->moveSpeed = moveSpeed;
    this->state = STATE_STANDING;
    currentDirection = MoveDirection::NONE;
}

void MovableEntity::update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    //TODO: the state machine idea would be to call state->onMoveEvent(this, direction) for each state. wouldn't have to switch on state anymore

    switch(state) {
        case STATE_STANDING:
            handleStandingState(deltaTime);
            break;
        case STATE_MOVING:
            handleMovingState(deltaTime, mapTileSize);
            break;
    }
}

void MovableEntity::handleStandingState(sf::Time deltaTime) {
    if(currentDirection != MoveDirection::NONE) {
        state = STATE_MOVING;
        performRegularMove(deltaTime);
    }
}

void MovableEntity::handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    //NOTE: using a moving goal limits me to making everything based on a set tile size (8 pixels for example). any collision bounds must be in multiples of 8 or entities won't collide correctly
    if(movementGoalReached(mapTileSize)) {
        if(currentDirection == MoveDirection::NONE) {
            state = STATE_STANDING;
        } else {
            state = STATE_MOVING;
            performRegularMove(deltaTime);
        }
    } else {
        //if we haven't reached the goal, don't change the state and keep moving
        performGoalLimitedMove(deltaTime, mapTileSize);
    }
}

bool MovableEntity::movementGoalReached(const sf::Vector2u& mapTileSize) {
    if(previousDirection == MoveDirection::NONE) {
        printf("MovableEntity.movementGoalReached().this should not be happening\n");
        return true;
    }

    int position = getChangingPosition(previousDirection, getPosition());
    int tileSize = getTileSizeForDirection(previousDirection, mapTileSize);
    return (position % tileSize == 0); //if tileSize is a multiple of position, then our goal is reached
}

sf::Vector2f MovableEntity::getGoalLimitedMovement(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {

    if(currentDirection == MoveDirection::NONE) {
        printf("this should not be happening. shouldn't be setting GoalLimitedMovement without a direction other than NONE. \n");
        return sf::Vector2f(0.f, 0.f);
    }

    int position = getChangingPosition(currentDirection, getPosition());
    int tileSize = getTileSizeForDirection(currentDirection, mapTileSize);
    int moveGoal = position + (tileSize - position % tileSize);
    sf::Vector2f move = getRegularMovement(moveSpeed) * deltaTime.asSeconds();

    float distanceToTravel = (currentDirection == MoveDirection::UP || currentDirection == MoveDirection::DOWN) ? move.y : move.x;
    float newMoveSpeed = moveSpeed;
    if((position + distanceToTravel) > moveGoal) {
        float newDistanceToTravel = (moveGoal - position);
        newMoveSpeed = newDistanceToTravel / deltaTime.asSeconds();
    }

    return getRegularMovement(newMoveSpeed);
}

sf::Vector2f MovableEntity::getRegularMovement(float speed) {
    sf::Vector2f movement;

    switch(currentDirection) {
        case MoveDirection::UP:
            movement.y -= speed;
            break;
        case MoveDirection::LEFT:
            movement.x -= speed;
            break;
        case MoveDirection::DOWN:
            movement.y += speed;
            break;
        case MoveDirection::RIGHT:
            movement.x += speed;
            break;
        default:
            printf("MovableEntity.getRegularMovement. this should not be happening\n");
            break;
    }

    currentlyFacingDirection = currentDirection; //setting this assuming that getRegularMovement would never be called if currentDirection == MoveDirection::NONE
    return movement;
}

void MovableEntity::performRegularMove(sf::Time deltaTime) {
    sf::Vector2f moveVector = getRegularMovement(moveSpeed);
    Sprite::move(moveVector * deltaTime.asSeconds());
    previousDirection = currentDirection;
}

void MovableEntity::performGoalLimitedMove(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    currentDirection = previousDirection;
    sf::Vector2f moveVector = getGoalLimitedMovement(deltaTime, mapTileSize);
    Sprite::move(moveVector * deltaTime.asSeconds());
    previousDirection = currentDirection; //TODO: verify this isn't needed
}

MoveDirection MovableEntity::getCurrentFacingDirection() {
    return this->currentlyFacingDirection;
}

MoveDirection MovableEntity::getCurrentDirection() {
    return this->currentDirection;
}

void MovableEntity::setCurrentDirection(MoveDirection direction) {
    this->currentDirection = direction;
}

int MovableEntity::getChangingPosition(const MoveDirection& direction, const sf::Vector2f& position) {
    switch(direction) {
        case MoveDirection::UP:
        case MoveDirection::DOWN:
            return position.y;
        case MoveDirection::LEFT:
        case MoveDirection::RIGHT:
            return position.x;
        default:
            printf("MovableEntity.getChangingPosition() returning a bad value\n");
            return 0;
    }
}

int MovableEntity::getTileSizeForDirection(const MoveDirection& direction, const sf::Vector2u& mapTileSize) {
    switch(direction) {
        case MoveDirection::UP:
        case MoveDirection::DOWN:
            return mapTileSize.y;
        case MoveDirection::LEFT:
        case MoveDirection::RIGHT:
            return mapTileSize.x;
        default:
            printf("MovableEntity.getTileSizeForDirection() returning a bad value\n");
            return 0;
    }
}