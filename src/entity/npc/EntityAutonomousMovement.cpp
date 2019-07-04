#include "../../../includes/entity/npc/EntityAutonomousMovement.h"

const sf::Vector2f moveDelayRange = sf::Vector2f(1.5f, 5.5f); //TODO: do i want this hardcoded?

void EntityAutonomousMovement::initialize(sf::IntRect moveBoundaries, float moveSpeed) {
    this->moveBoundaries = moveBoundaries;
    this->moveSpeed = moveSpeed;
    entityMovement.initialize(moveSpeed);
    setMoveDelayTimer();
}

void EntityAutonomousMovement::handleStanding(sf::Time deltaTime, const sf::Vector2u& mapTileSize, EntityState& state,
        sf::Vector2f& currentPosition) {
    if(moveDelayTimerDone(deltaTime)) {
        setupEntityMovement(mapTileSize, state, currentPosition);
    }
}

void EntityAutonomousMovement::handleMoving(sf::Time deltaTime, const sf::Vector2u& mapTileSize,
        sf::Vector2f& currentPosition, EntityState& state) {
    sf::Vector2f previousPosition = currentPosition;
    entityMovement.performRegularMoveOnCurrentPosition(deltaTime, currentDirection, currentPosition);

    sf::Vector2f distanceTravelledThisFrame = currentPosition;
    distanceTravelledThisFrame -= previousPosition;
    switch(currentDirection) {
        case MoveDirection::UP:
        case MoveDirection::DOWN:
            distanceMoved += abs(distanceTravelledThisFrame.y);
            break;
        case MoveDirection::LEFT:
        case MoveDirection::RIGHT:
            distanceMoved += abs(distanceTravelledThisFrame.x);
            break;
        default:
            printf("EntityAutonomousMovement::moveEntityTowardMovementGoal -- Invalid currentDirection value\n");
            break;
    }

    if(distanceMoved >= movementGoal) {
        ensureEntityPositionAlignedWithTileSize(mapTileSize, currentPosition);
        ensureEntityInsideBounds(currentPosition);

        state = STATE_STANDING;
        currentDirection = MoveDirection::NONE;
        distanceMoved = 0;
    }
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

void EntityAutonomousMovement::setupEntityMovement(const sf::Vector2u& mapTileSize, EntityState& state, sf::Vector2f& currentPosition) {
    if (decideIfNpcShouldMove()) {
        MoveDirection moveDirection = chooseRandomDirection();
        int maxDistanceEntityCanTravel = getMaxDistanceEntityCanTravel(moveDirection, currentPosition);
        if(maxDistanceEntityCanTravel > 0) {
            int tileSize = getTileSizeForDirection(moveDirection, mapTileSize);
            this->movementGoal = determineRandomDistanceToMoveEntity(maxDistanceEntityCanTravel, tileSize);
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

void EntityAutonomousMovement::ensureEntityPositionAlignedWithTileSize(const sf::Vector2u& mapTileSize, sf::Vector2f& currentPosition) {
    int x = currentPosition.x;
    int y = currentPosition.y;
    int xRemainder = x % mapTileSize.x;
    int yRemainder = y % mapTileSize.y;

    if(xRemainder != 0) {
        printf("position is bad and its being adjusted in EntityAutonomousMovement::ensureEntityPositionAlignedWithTileSize\n");
        currentPosition.x = x - xRemainder;
    }
    if(yRemainder != 0) {
        printf("position is bad and its being adjusted in EntityAutonomousMovement::ensureEntityPositionAlignedWithTileSize\n");
        currentPosition.y = y - yRemainder;
    }
}

void EntityAutonomousMovement::ensureEntityInsideBounds(sf::Vector2f& currentPosition) {
    if(currentPosition.x > (moveBoundaries.left + moveBoundaries.width)) {
        printf("moved too far to the right of boundary, fixing in EntityAutonomousMovement::ensureEntityInsideBounds\n");
        currentPosition.x = moveBoundaries.left + moveBoundaries.width;
    }
    if(currentPosition.x < moveBoundaries.left) {
        printf("moved too far to the left of boundary, fixing in EntityAutonomousMovement::ensureEntityInsideBounds\n");
        currentPosition.x = moveBoundaries.left;
    }
    if(currentPosition.y > (moveBoundaries.top + moveBoundaries.height)) {
        printf("moved too far down of boundary, fixing in EntityAutonomousMovement::ensureEntityInsideBounds\n");
        currentPosition.y = moveBoundaries.top + moveBoundaries.height;
    }
    if(currentPosition.y < moveBoundaries.top) {
        printf("moved too far up of boundary, fixing in EntityAutonomousMovement::ensureEntityInsideBounds\n");
        currentPosition.y = moveBoundaries.top;
    }
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
        minDistanceEntityCanTravel = 0; //TODO: if this happens, then the NPC is in a weird place and it needs to be corrected. Will this correct it?
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

void EntityAutonomousMovement::resetDistanceMoved() {
    distanceMoved = 0;
}

MoveDirection EntityAutonomousMovement::getCurrentDirection() {
    return this->currentDirection;
}

void EntityAutonomousMovement::setCurrentDirection(MoveDirection direction) {
    currentDirection = direction;
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