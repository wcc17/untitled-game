#include "../../../includes/entity/character/MovableEntity.h"

void MovableEntity::initialize(float moveSpeed) {
    this->moveSpeed = moveSpeed;
    this->state = STATE_STANDING;
}

//TODO: this should be called in an update function, ditch the seperate move function?
void MovableEntity::move(sf::Time deltaTime, MoveDirection direction, sf::Vector2u mapTileSize) {
    //TODO: the state machine idea would be to call state->onMoveEvent(this, direction) for each state. wouldn't have to switch on state anymore
    //TODO: is it worth it at this point to move to the state machine? what sort of states do i need to implement if thats the case?

    switch(state) {
        case STATE_STANDING:
            handleStandingState(direction, deltaTime);
            break;
        case STATE_MOVING:
            handleMovingState(direction, deltaTime, mapTileSize);
            break;
    }
}

void MovableEntity::handleStandingState(MoveDirection direction, sf::Time deltaTime) {
    currentDirection = direction;

    if(direction != MoveDirection::NONE) {
        state = STATE_MOVING; 
        performRegularMove(deltaTime);
    }
}

void MovableEntity::handleMovingState(MoveDirection direction, sf::Time deltaTime, sf::Vector2u mapTileSize) {
    currentDirection = direction;

    //NOTE: using a moving goal limits me to making everything based on a set tile size (8 pixels for example). any collision bounds must be in multiples of 8 or entities won't collide correctly
    if(movementGoalReached(mapTileSize)) {
        if(direction == MoveDirection::NONE) {
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

bool MovableEntity::movementGoalReached(sf::Vector2u mapTileSize) {
    if(previousDirection == MoveDirection::NONE) {
        printf("MovableEntity.movementGoalReached().this should not be happening\n");
        return true;
    }

    int position = getChangingPosition(previousDirection, getPosition());
    int tileSize = getTileSizeForDirection(previousDirection, mapTileSize);
    return (position % tileSize == 0); //if tileSize is a multiple of position, then our goal is reached
}

sf::Vector2f MovableEntity::getGoalLimitedMovement(sf::Time deltaTime, sf::Vector2u mapTileSize) {

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

    return movement;
}

void MovableEntity::performRegularMove(sf::Time deltaTime) {
    sf::Vector2f moveVector = getRegularMovement(moveSpeed);
    Sprite::move(moveVector * deltaTime.asSeconds());
    previousDirection = currentDirection; 
}

void MovableEntity::performGoalLimitedMove(sf::Time deltaTime, sf::Vector2u mapTileSize) {
    currentDirection = previousDirection;
    sf::Vector2f moveVector = getGoalLimitedMovement(deltaTime, mapTileSize);
    Sprite::move(moveVector * deltaTime.asSeconds());
    previousDirection = currentDirection; 
}

//TODO: would it make more sense if this was in MovableEntity?
//TODO: EVERYTHING needs to be multiples of  tile size, including the character textures (its frames). There should be a check to ensure this is happening so that I don't forget
sf::Vector2f MovableEntity::getFixedPositionAfterCollision(sf::FloatRect entityRect, sf::FloatRect otherRect, MoveDirection direction) {
    bool isColliding = true;
    float left = entityRect.left;
    float top = entityRect.top;
    while(isColliding) {
        if(direction == MoveDirection::NONE) {
            printf("error with player collision - the player didn't move into this collision so theres no way to move him out\n");
        }

        if(direction == MoveDirection::RIGHT) {
            left -= 1;
        } else if(direction == MoveDirection::LEFT) {
            left += 1;
        }

        if(direction == MoveDirection::DOWN) {
            top -= 1;
        } else if(direction == MoveDirection::UP) {
            top += 1;
        }

        sf::FloatRect newBounds = sf::FloatRect(left, top, entityRect.width, entityRect.height);
        if(!newBounds.intersects(otherRect)) {
            isColliding = false;
        }
    }

    setPosition(sf::Vector2f(left, top));
}

MoveDirection MovableEntity::getCurrentDirection() {
    return this->currentDirection;
}

int MovableEntity::getChangingPosition(MoveDirection direction, sf::Vector2f position) {
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

int MovableEntity::getTileSizeForDirection(MoveDirection direction, sf::Vector2u mapTileSize) {
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