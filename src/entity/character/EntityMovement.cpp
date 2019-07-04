#include "../../../includes/entity/character/EntityMovement.h"

void EntityMovement::initialize(float moveSpeed) {
    this->moveSpeed = moveSpeed;
    previousDirection = MoveDirection::UP;
}

void EntityMovement::handleStandingState(sf::Time deltaTime, EntityState& state, MoveDirection& currentDirection, sf::Vector2f& currentPosition) {
    if(currentDirection != MoveDirection::NONE) {
        state = STATE_MOVING;
        performRegularMove(deltaTime, currentDirection, currentPosition);
    }
}

void EntityMovement::handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize, EntityState& state,
        MoveDirection& currentDirection, sf::Vector2f& currentPosition) {
    if(movementGoalReached(mapTileSize, currentPosition)) {
        if(currentDirection == MoveDirection::NONE) {
            state = STATE_STANDING;
        } else {
            state = STATE_MOVING;
            performRegularMove(deltaTime, currentDirection, currentPosition);
        }
    } else {
        //if we haven't reached the goal, don't change the state and keep moving
        performGoalLimitedMove(deltaTime, mapTileSize, currentDirection, currentPosition);
    }
}

bool EntityMovement::movementGoalReached(const sf::Vector2u& mapTileSize, sf::Vector2f currentPosition) {
    if(previousDirection == MoveDirection::NONE) {
        printf("MovableEntity.movementGoalReached().this should not be happening\n");
        return true;
    }

    int position = getChangingPosition(previousDirection, currentPosition);
    int tileSize = getTileSizeForDirection(previousDirection, mapTileSize);
    return (position % tileSize == 0); //if tileSize is a multiple of position, then our goal is reached
}

sf::Vector2f EntityMovement::getGoalLimitedMovement(sf::Time deltaTime, const sf::Vector2u& mapTileSize,
        MoveDirection& currentDirection, sf::Vector2f currentPosition) {

    if(currentDirection == MoveDirection::NONE) {
        printf("this should not be happening. shouldn't be setting GoalLimitedMovement without a direction other than NONE. \n");
        return sf::Vector2f(0.f, 0.f);
    }

    int position = getChangingPosition(currentDirection, currentPosition);
    int tileSize = getTileSizeForDirection(currentDirection, mapTileSize);
    int moveGoal = position + (tileSize - position % tileSize);
    sf::Vector2f move = getRegularMovement(moveSpeed, currentDirection) * deltaTime.asSeconds();

    float distanceToTravel = (currentDirection == MoveDirection::UP || currentDirection == MoveDirection::DOWN) ? move.y : move.x;
    float newMoveSpeed = moveSpeed;
    if((position + distanceToTravel) > moveGoal) {
        float newDistanceToTravel = (moveGoal - position);
        newMoveSpeed = newDistanceToTravel / deltaTime.asSeconds();
    }

    return getRegularMovement(newMoveSpeed, currentDirection);
}

sf::Vector2f EntityMovement::getRegularMovement(float speed, MoveDirection& currentDirection) {
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

    lastFacingDirection = currentDirection; //setting this assuming that getRegularMovement would never be called if currentDirection == MoveDirection::NONE
    return movement;
}

void EntityMovement::performRegularMove(sf::Time deltaTime, MoveDirection& currentDirection, sf::Vector2f& currentPosition) {
    sf::Vector2f moveVector = getRegularMovement(moveSpeed, currentDirection);
    sf::Vector2f moveVectorWithSpeed = moveVector * deltaTime.asSeconds();
    currentPosition = sf::Vector2f(currentPosition.x + moveVectorWithSpeed.x, currentPosition.y + moveVectorWithSpeed.y);
    previousDirection = currentDirection;
}

void EntityMovement::performGoalLimitedMove(sf::Time deltaTime, const sf::Vector2u& mapTileSize,
        MoveDirection& currentDirection, sf::Vector2f& currentPosition) {
    currentDirection = previousDirection;
    sf::Vector2f moveVector = getGoalLimitedMovement(deltaTime, mapTileSize, currentDirection, currentPosition);
    sf::Vector2f moveVectorWithSpeed = moveVector * deltaTime.asSeconds();
    currentPosition = sf::Vector2f(currentPosition.x + moveVectorWithSpeed.x, currentPosition.y + moveVectorWithSpeed.y);
    previousDirection = currentDirection;
}

MoveDirection EntityMovement::getLastFacingDirection() {
    return this->lastFacingDirection;
}

int EntityMovement::getChangingPosition(const MoveDirection& direction, const sf::Vector2f& position) {
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

int EntityMovement::getTileSizeForDirection(const MoveDirection& direction, const sf::Vector2u& mapTileSize) {
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