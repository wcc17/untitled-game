#include "../../../includes/entity/npc/EntityAutonomousMovement.h"

const sf::Vector2f moveDelayRange = sf::Vector2f(1.5f, 5.5f); //TODO: do i want this hardcoded?

void EntityAutonomousMovement::initialize(sf::IntRect moveBoundaries, float moveSpeed) {
    this->moveBoundaries = moveBoundaries;
    this->moveSpeed = moveSpeed;
    setMoveDelayTimer();
}

void EntityAutonomousMovement::handleStanding(sf::Time deltaTime, const sf::Vector2u& mapTileSize, EntityState& state,
        const sf::Vector2f& currentPosition) {
    if(moveDelayTimerDone(deltaTime)) {
        setupEntityMovement(mapTileSize, state, currentPosition);
    }
}

sf::Vector2f EntityAutonomousMovement::handleMoveAndReturnPosition(sf::Time deltaTime, sf::Vector2f currentPosition, EntityState& state) {
    move(deltaTime, currentPosition);
    checkMovementGoal(currentPosition, state);
    return currentPosition;
}

void EntityAutonomousMovement::move(sf::Time deltaTime, sf::Vector2f& currentPosition) {
    sf::Vector2f moveVector = getRegularMovement(moveSpeed);
    sf::Vector2f moveVectorWithSpeed = moveVector * deltaTime.asSeconds();
    currentPosition = sf::Vector2f(currentPosition.x + moveVectorWithSpeed.x, currentPosition.y + moveVectorWithSpeed.y);
}

void EntityAutonomousMovement::checkMovementGoal(sf::Vector2f& currentPosition, EntityState& state) {
    switch(currentDirection) {
        case MoveDirection::UP:
            if(currentPosition.y < movementGoal) {
                currentPosition.y = movementGoal;
                stopMovement(state);
            }
            break;
        case MoveDirection::DOWN:
            if(currentPosition.y > movementGoal) {
                currentPosition.y = movementGoal;
                stopMovement(state);
            }
            break;
        case MoveDirection::LEFT:
            if(currentPosition.x < movementGoal) {
                currentPosition.x = movementGoal;
                stopMovement(state);
            }
            break;
        case MoveDirection::RIGHT:
            if(currentPosition.x > movementGoal) {
                currentPosition.x = movementGoal;
                stopMovement(state);
            }
            break;
        default:
            printf("Invalid\n");
            break;
    }
}

void EntityAutonomousMovement::stopMovement(EntityState& state) {
    state = STATE_STANDING;
    currentDirection = MoveDirection::NONE;
}

sf::Vector2f EntityAutonomousMovement::getRegularMovement(float speed) {
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
            printf("EntityAutonomousMovement.getRegularMovement. this should not be happening\n");
            break;
    }

    return movement;
}

bool EntityAutonomousMovement::moveDelayTimerDone(sf::Time deltaTime) {
    this->moveDelay -= deltaTime;
    if (this->moveDelay <= sf::Time::Zero) {
        setMoveDelayTimer();
        return true;
    }

    return false;
}

void EntityAutonomousMovement::setMoveDelayTimer() {
    float min = moveDelayRange.x;
    float max = moveDelayRange.y;
    float delay = getRandomFloatInRange(min, max);

    printf("\n");
    if(delay > max || delay < min) {
        printf("invalid value in EntityAutonomousMovement::setMoveDelayTimer\n");
    }
    printf("move delay timer set to %f\n", delay);

    this->moveDelay = sf::seconds(delay);
}

void EntityAutonomousMovement::setupEntityMovement(const sf::Vector2u& mapTileSize, EntityState& state, const sf::Vector2f& currentPosition) {
    if (decideIfNpcShouldMove()) {
        MoveDirection moveDirection = chooseRandomDirection();
        int maxDistanceEntityCanTravel = getMaxDistanceEntityCanTravel(moveDirection, currentPosition);
        if(maxDistanceEntityCanTravel > 0) {
            int tileSize = getTileSizeForDirection(moveDirection, mapTileSize);
            int distance = determineRandomDistanceToMoveEntity(maxDistanceEntityCanTravel, tileSize);

            switch(moveDirection) {
                case MoveDirection::UP:
                    movementGoal = currentPosition.y - distance;
                    break;
                case MoveDirection::DOWN:
                    movementGoal = currentPosition.y + distance;
                    break;
                case MoveDirection::LEFT:
                    movementGoal = currentPosition.x - distance;
                    break;
                case MoveDirection::RIGHT:
                    movementGoal = currentPosition.x + distance;
                    break;
                default:
                    printf("invalid\n");
                    break;
            }

            this->currentDirection = moveDirection;
            state = STATE_MOVING;
        } else {
            printf("entity is not going to move after all\n");
        }
    }
}

int EntityAutonomousMovement::getMaxDistanceEntityCanTravel(MoveDirection moveDirection, sf::Vector2f currentPosition) {
    int maxDistanceEntityCanTravel;
    switch (moveDirection) {
        case 1:
            maxDistanceEntityCanTravel = moveBoundaries.top;
            maxDistanceEntityCanTravel = currentPosition.y - maxDistanceEntityCanTravel;
            printf("npc wants to move up\n");
            break;
        case 2:
            maxDistanceEntityCanTravel = moveBoundaries.top + moveBoundaries.height;
            maxDistanceEntityCanTravel -= currentPosition.y;
            printf("npc wants to move down\n");
            break;
        case 3:
            maxDistanceEntityCanTravel = moveBoundaries.left;
            maxDistanceEntityCanTravel = currentPosition.x - maxDistanceEntityCanTravel;
            printf("npc wants to move left\n");
            break;
        case 4:
            maxDistanceEntityCanTravel = moveBoundaries.left + moveBoundaries.width;
            maxDistanceEntityCanTravel -= currentPosition.x;
            printf("npc wants to move right\n");
            break;
        default:
            printf("Assigned an invalid direction in EntityAutonomousMovement::getMaxDistanceEntityCanTravel\n");
            maxDistanceEntityCanTravel = 0;
            break;
    }

    printf("current position: %f, %f\n", currentPosition.x, currentPosition.y);
    printf("bounds: left: %i, top: %i, width: %i, height: %i\n", moveBoundaries.left, moveBoundaries.top, moveBoundaries.width, moveBoundaries.height);
    printf("max distance: %i\n", maxDistanceEntityCanTravel);
    return maxDistanceEntityCanTravel;
}

bool EntityAutonomousMovement::decideIfNpcShouldMove() {
    int shouldMove = getRandomIntInRange(1, 5);
    if(shouldMove > 5 || shouldMove < 1) {
        printf("wrong shouldMove value in EntityAutonomousMovement::decideIfNpcShouldMove\n");
    }
    return (shouldMove <= 3);
}

MoveDirection EntityAutonomousMovement::chooseRandomDirection() {
    int randomDirection = getRandomIntInRange(1, 4);
    if(randomDirection > 4 || randomDirection < 1) {
        randomDirection = 0;
        printf("wrong direction chosen in EntityAutonomousMovement::chooseRandomDirection\n");
    }

    return static_cast<MoveDirection>(randomDirection);
}

int EntityAutonomousMovement::determineRandomDistanceToMoveEntity(int maxDistanceEntityCanTravel, int tileSize) {
    int distanceToMoveEntity = 0;

    int minDistanceEntityCanTravel = tileSize;
    if(maxDistanceEntityCanTravel < minDistanceEntityCanTravel) {
        printf("Npc::Entity::determineRandomDistanceToMoveEntity got a max distance less than tile size. Need to verify that this corrected the npc's position\n");
        minDistanceEntityCanTravel = 0;
    }

    if(tileSize > 0 && maxDistanceEntityCanTravel > 0) {
        distanceToMoveEntity = getRandomIntInRange(minDistanceEntityCanTravel, maxDistanceEntityCanTravel);
        printf("random distance chosen: %i\n", distanceToMoveEntity);

        //make the distance the highest multiple of tileSize possible
        int remainder = distanceToMoveEntity % tileSize;
        if ( (distanceToMoveEntity + (tileSize - remainder)) < maxDistanceEntityCanTravel) {
            distanceToMoveEntity += (tileSize - remainder);
        } else {
            distanceToMoveEntity -= remainder;
        }

        if (distanceToMoveEntity % tileSize != 0) {
            printf("EntityAutonomousMovement is trying to move in a distance that isn't a multiple of the tile size\n");
            distanceToMoveEntity = 0;
        }
    }

    printf("is going to move with distance: %i\n", distanceToMoveEntity);
    return distanceToMoveEntity;
}

int EntityAutonomousMovement::getTileSizeForDirection(MoveDirection moveDirection, const sf::Vector2u& mapTileSize) {
    switch (moveDirection) {
        case MoveDirection::UP:
        case MoveDirection::DOWN:
            return mapTileSize.y;
        case MoveDirection::LEFT:
        case MoveDirection::RIGHT:
            return mapTileSize.x;
        default:
            printf("EntityAutonomousMovement.getTileSizeForDirection was given an invalid direction\n");
            return 0;
    }
}

MoveDirection EntityAutonomousMovement::getCurrentDirection() {
    return this->currentDirection;
}

//TODO: these probably belong in a utility class somewhere
int EntityAutonomousMovement::getRandomIntInRange(int min, int max) {
    std::mt19937 eng(randomDevice());
    std::uniform_int_distribution<> distr(min, max); // define the range
    return distr(eng);
}

float EntityAutonomousMovement::getRandomFloatInRange(float min, float max) {
    std::mt19937 eng(randomDevice());
    std::uniform_real_distribution<float> distr(min, max); // define the range
    return distr(eng);
}