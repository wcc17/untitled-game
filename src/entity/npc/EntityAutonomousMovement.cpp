#include "../../../includes/entity/npc/EntityAutonomousMovement.h"

const sf::Vector2f moveDelayRange = sf::Vector2f(1.5f, 5.5f); //TODO: do i want this hardcoded?
Logger EntityAutonomousMovement::logger("EntityAutonomousMovement");

void EntityAutonomousMovement::initialize(std::string npcName, sf::IntRect moveBoundaries, float moveSpeed) {
    this->npcName = npcName;
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
            logError("Invalid direction when checking movement goal in EntityAutonomousMovement.checkMovementGoal");
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
            logError("EntityAutonomousMovement.getRegularMovement. this should not be happening");
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

    logDebug("");
    logDebug("move delay timer set to %f", delay);

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
                    logError("invalid direction");
                    break;
            }

            this->currentDirection = moveDirection;
            state = STATE_MOVING;
        } else {
            logDebug("entity is not going to move after all");
        }
    }
}

int EntityAutonomousMovement::getMaxDistanceEntityCanTravel(MoveDirection moveDirection, sf::Vector2f currentPosition) {
    int maxDistanceEntityCanTravel;
    switch (moveDirection) {
        case 1:
            maxDistanceEntityCanTravel = moveBoundaries.top;
            maxDistanceEntityCanTravel = currentPosition.y - maxDistanceEntityCanTravel;
            logDebug("npc wants to move up");
            break;
        case 2:
            maxDistanceEntityCanTravel = moveBoundaries.top + moveBoundaries.height;
            maxDistanceEntityCanTravel -= currentPosition.y;
            logDebug("npc wants to move down");
            break;
        case 3:
            maxDistanceEntityCanTravel = moveBoundaries.left;
            maxDistanceEntityCanTravel = currentPosition.x - maxDistanceEntityCanTravel;
            logDebug("npc wants to move left");
            break;
        case 4:
            maxDistanceEntityCanTravel = moveBoundaries.left + moveBoundaries.width;
            maxDistanceEntityCanTravel -= currentPosition.x;
            logDebug("npc wants to move right");
            break;
        default:
            logError("Assigned an invalid direction in EntityAutonomousMovement::getMaxDistanceEntityCanTravel");
            maxDistanceEntityCanTravel = 0;
            break;
    }

    logDebug("current position: %f, %f", currentPosition.x, currentPosition.y);
    logDebug("bounds: left: %i, top: %i, width: %i, height: %i", moveBoundaries.left, moveBoundaries.top, moveBoundaries.width, moveBoundaries.height);
    logDebug("max distance: %i", maxDistanceEntityCanTravel);
    return maxDistanceEntityCanTravel;
}

bool EntityAutonomousMovement::decideIfNpcShouldMove() {
    int shouldMove = getRandomIntInRange(1, 5);
    return (shouldMove <= 3);
}

MoveDirection EntityAutonomousMovement::chooseRandomDirection() {
    int randomDirection = getRandomIntInRange(1, 4);
    return static_cast<MoveDirection>(randomDirection);
}

int EntityAutonomousMovement::determineRandomDistanceToMoveEntity(int maxDistanceEntityCanTravel, int tileSize) {
    int distanceToMoveEntity = 0;

    int minDistanceEntityCanTravel = tileSize;
    if(maxDistanceEntityCanTravel < minDistanceEntityCanTravel) {
        logDebug("Npc::Entity::determineRandomDistanceToMoveEntity got a max distance less than tile size. Need to verify that this corrected the npc's position");
        minDistanceEntityCanTravel = 0;
    }

    if(tileSize > 0 && maxDistanceEntityCanTravel > 0) {
        distanceToMoveEntity = getRandomIntInRange(minDistanceEntityCanTravel, maxDistanceEntityCanTravel);
        logDebug("random distance chosen: %i", distanceToMoveEntity);

        //make the distance the highest multiple of tileSize possible
        int remainder = distanceToMoveEntity % tileSize;
        if ( (distanceToMoveEntity + (tileSize - remainder)) < maxDistanceEntityCanTravel) {
            distanceToMoveEntity += (tileSize - remainder);
        } else {
            distanceToMoveEntity -= remainder;
        }

        if (distanceToMoveEntity % tileSize != 0) {
            logError("EntityAutonomousMovement is trying to move in a distance that isn't a multiple of the tile size");
            distanceToMoveEntity = 0;
        }
    }

    logDebug("is going to move with distance: %i", distanceToMoveEntity);
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
            logError("EntityAutonomousMovement.getTileSizeForDirection was given an invalid direction");
            return 0;
    }
}

MoveDirection EntityAutonomousMovement::getCurrentDirection() {
    return this->currentDirection;
}

void EntityAutonomousMovement::logDebug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logger.logDebugWithPrepend(npcName + " - ", format, args);
    va_end(args);
}

void EntityAutonomousMovement::logError(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logger.logErrorWithPrepend(npcName, format, args);
    va_end(args);
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