#include "../../../includes/entity/character/NpcEntity.h"

const float ENTITY_WIDTH = 16.f;
const float ENTITY_HEIGHT = 24.f;
const float ENTITY_MOVEMENT_SPEED = 65.f;
const float ENTITY_FRAME_TIME = 0.16f; //TODO: not sure where I want to load this from yet

const sf::Vector2f moveDelayRange = sf::Vector2f(1.5f, 5.5f);

void NpcEntity::initialize(sf::Texture* texture, const Collidable& collidable, sf::IntRect moveBoundaries) {
    MovableEntity::setTexture(*texture);
    MovableEntity::initialize(ENTITY_MOVEMENT_SPEED);

    this->state = STATE_STANDING;
    this->entityCollidable.setName(collidable.getName());
    this->entityCollidable.setType(collidable.getType());
    this->entityCollidable.setBoundingBox(collidable.getBoundingBox());
    this->setPosition(sf::Vector2f(collidable.getBoundingBox().left, collidable.getBoundingBox().top));

    entityAnimation.setFrameTime(sf::seconds(ENTITY_FRAME_TIME));
    initializeAnimations();

    this->moveBoundaries = moveBoundaries;
    setMoveDelayTimer();
}

void NpcEntity::update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    switch(state) {
        case STATE_STANDING:
            handleStandingState(deltaTime, mapTileSize);
            break;
        case STATE_MOVING:
            handleMovingState(deltaTime, mapTileSize);
            break;
        case STATE_INTERACTING:
            handleInteractingState();
            break;
    }

    //TODO: remove all of this soon
    if(state == STATE_STANDING) {
        int x = getPosition().x;
        int y = getPosition().y;
        int xRemainder = x % mapTileSize.x;
        int yRemainder = y % mapTileSize.y;
        if(xRemainder != 0) {
            printf("position is bad and its being adjusted in NpcEntity::ensureEntityPositionAlignedWithTileSize\n");
        }
        if(yRemainder != 0) {
            printf("position is bad and its being adjusted in NpcEntity::ensureEntityPositionAlignedWithTileSize\n");
        }
        if(getPosition().x > (moveBoundaries.left + moveBoundaries.width)) {
            printf("moved too far to the right of boundary, fixing in NpcEntity::ensureEntityInsideBounds\n");
        }
        if(getPosition().x < moveBoundaries.left) {
            printf("moved too far to the left of boundary, fixing in NpcEntity::ensureEntityInsideBounds\n");
        }
        if(getPosition().y > (moveBoundaries.top + moveBoundaries.height)) {
            printf("moved too far down of boundary, fixing in NpcEntity::ensureEntityInsideBounds\n");
        }
        if(getPosition().y < moveBoundaries.top) {
            printf("moved too far up of boundary, fixing in NpcEntity::ensureEntityInsideBounds\n");
        }
    }

    //TODO: this should be in the handleState functions
    MovableEntity::setTextureRect(entityAnimation.getTextureRect());
    this->entityCollidable.setBoundingBox(sf::FloatRect(getPosition().x, getPosition().y, ENTITY_WIDTH, ENTITY_HEIGHT));
}

void NpcEntity::onPlayerInteractionStart(MoveDirection playerFacingDirection) {
    entityAnimation.turnToFaceEntityFacingDirection(playerFacingDirection);
    state = STATE_INTERACTING;
    //TODO: can this put the entity in a weird position? Will it be fixed?
}

void NpcEntity::onPlayerInteractionFinish() {
    state = STATE_STANDING;
    currentDirection = MoveDirection::NONE;
    distanceMoved = 0;
}

void NpcEntity::onCollisionEvent(const Collidable& collidedWith) {
//    CollidableEntity::fixPositionAfterCollision(collidedWith, currentDirection);
//    roundPosition();
}

void NpcEntity::handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    MovableEntity::handleStandingState(deltaTime, state);
    entityAnimation.update(deltaTime, currentDirection);

    roundPosition();

    if(moveDelayTimerDone(deltaTime)) {
        setupEntityMovement(mapTileSize);
    }
}

void NpcEntity::handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    entityAnimation.update(deltaTime, currentDirection);
    handleEntityMovementTowardGoal(deltaTime, mapTileSize);
}

void NpcEntity::handleInteractingState() { }

bool NpcEntity::moveDelayTimerDone(sf::Time deltaTime) {
    this->moveDelay -= deltaTime;
    if (this->moveDelay <= sf::Time::Zero) {
        setMoveDelayTimer();
        return true;
    }

    return false;
}

void NpcEntity::setMoveDelayTimer() {
    float min = moveDelayRange.x;
    float max = moveDelayRange.y;
    float delay = getRandomFloatInRange(min, max);

    printf("\n");
    if(delay > max || delay < min) {
        printf("invalid value in NpcEntity::setMoveDelayTimer\n");
    }
    printf("move delay timer set to %f\n", delay);

    this->moveDelay = sf::seconds(delay);
}

//TODO: should all of this npc movement setup be in its own class? I don't think it should be a parent class, look into c++ composition.
void NpcEntity::setupEntityMovement(const sf::Vector2u& mapTileSize) {
    if (decideIfNpcShouldMove()) {
        MoveDirection moveDirection = chooseRandomDirection();
        int maxDistanceEntityCanTravel = getMaxDistanceEntityCanTravel(moveDirection);
        if(maxDistanceEntityCanTravel > 0) {
            int tileSize = getTileSizeForDirection(moveDirection, mapTileSize);
            this->movementGoal = determineRandomDistanceToMoveEntity(maxDistanceEntityCanTravel, tileSize);
            this->state = STATE_MOVING;
            this->currentDirection = moveDirection;
        } else {
            printf("entity is not going to move after all\n");
        }
    }
}

int NpcEntity::getMaxDistanceEntityCanTravel(MoveDirection moveDirection) {
    int maxDistanceEntityCanTravel;
    switch (moveDirection) {
        case 1:
            maxDistanceEntityCanTravel = moveBoundaries.top;
            maxDistanceEntityCanTravel = getPosition().y - maxDistanceEntityCanTravel;
            printf("npc wants to move up\n");
            break;
        case 2:
            maxDistanceEntityCanTravel = moveBoundaries.top + moveBoundaries.height;
            maxDistanceEntityCanTravel -= getPosition().y;
            printf("npc wants to move down\n");
            break;
        case 3:
            maxDistanceEntityCanTravel = moveBoundaries.left;
            maxDistanceEntityCanTravel = getPosition().x - maxDistanceEntityCanTravel;
            printf("npc wants to move left\n");
            break;
        case 4:
            maxDistanceEntityCanTravel = moveBoundaries.left + moveBoundaries.width;
            maxDistanceEntityCanTravel -= getPosition().x;
            printf("npc wants to move right\n");
            break;
        default:
            printf("Assigned an invalid direction in NpcEntity::getMaxDistanceEntityCanTravel\n");
            maxDistanceEntityCanTravel = 0;
            break;
    }

    printf("current position: %f, %f\n", getPosition().x, getPosition().y);
    printf("bounds: left: %i, top: %i, width: %i, height: %i\n", moveBoundaries.left, moveBoundaries.top, moveBoundaries.width, moveBoundaries.height);
    printf("max distance: %i\n", maxDistanceEntityCanTravel);
    return maxDistanceEntityCanTravel;
}

void NpcEntity::handleEntityMovementTowardGoal(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    sf::Vector2f previousPosition = getPosition();
    sf::Vector2f moveVector = getRegularMovement(80.f);
    Sprite::move(moveVector * deltaTime.asSeconds());
    roundPosition();

    sf::Vector2f distanceTravelledThisFrame = getPosition();
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
            printf("NpcEntity::moveEntityTowardMovementGoal -- Invalid currentDirection value\n");
            break;
    }

    if(distanceMoved >= movementGoal) {
        ensureEntityPositionAlignedWithTileSize(mapTileSize);
        ensureEntityInsideBounds();

        state = STATE_STANDING;
        currentDirection = MoveDirection::NONE;
        distanceMoved = 0;
    }
}

void NpcEntity::ensureEntityPositionAlignedWithTileSize(const sf::Vector2u& mapTileSize) {
    int x = getPosition().x;
    int y = getPosition().y;
    int xRemainder = x % mapTileSize.x;
    int yRemainder = y % mapTileSize.y;

    if(xRemainder != 0) {
        printf("position is bad and its being adjusted in NpcEntity::ensureEntityPositionAlignedWithTileSize\n");
        setPosition((x - xRemainder), y);
    }
    if(yRemainder != 0) {
        printf("position is bad and its being adjusted in NpcEntity::ensureEntityPositionAlignedWithTileSize\n");
        setPosition(x, (y - yRemainder));
    }
}

void NpcEntity::ensureEntityInsideBounds() {
    if(getPosition().x > (moveBoundaries.left + moveBoundaries.width)) {
        printf("moved too far to the right of boundary, fixing in NpcEntity::ensureEntityInsideBounds\n");
        setPosition((moveBoundaries.left + moveBoundaries.width), getPosition().y);
    }
    if(getPosition().x < moveBoundaries.left) {
        printf("moved too far to the left of boundary, fixing in NpcEntity::ensureEntityInsideBounds\n");
        setPosition(moveBoundaries.left, getPosition().y);
    }
    if(getPosition().y > (moveBoundaries.top + moveBoundaries.height)) {
        printf("moved too far down of boundary, fixing in NpcEntity::ensureEntityInsideBounds\n");
        setPosition(getPosition().x, (moveBoundaries.top + moveBoundaries.height));
    }
    if(getPosition().y < moveBoundaries.top) {
        printf("moved too far up of boundary, fixing in NpcEntity::ensureEntityInsideBounds\n");
        setPosition(getPosition().x, moveBoundaries.top);
    }
}

bool NpcEntity::decideIfNpcShouldMove() {
    int shouldMove = getRandomIntInRange(1, 5);
    if(shouldMove > 5 || shouldMove < 1) {
        printf("wrong shouldMove value in NpcEntity::decideIfNpcShouldMove\n");
    }
    return (shouldMove <= 3);
}

MoveDirection NpcEntity::chooseRandomDirection() {
    int randomDirection = getRandomIntInRange(1, 4);
    if(randomDirection > 4 || randomDirection < 1) {
        randomDirection = 0;
        printf("wrong direction chosen in NpcEntity::chooseRandomDirection\n");
    }

    return static_cast<MoveDirection>(randomDirection);
}

int NpcEntity::determineRandomDistanceToMoveEntity(int maxDistanceEntityCanTravel, int tileSize) {
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
            printf("NpcEntity is trying to move in a distance that isn't a multiple of the tile size\n");
            distanceToMoveEntity = 0;
        }
    }

    printf("is going to move with distance: %i\n", distanceToMoveEntity);
    return distanceToMoveEntity;
}

int NpcEntity::getTileSizeForDirection(MoveDirection moveDirection, const sf::Vector2u& mapTileSize) {
    switch (moveDirection) {
        case MoveDirection::UP:
        case MoveDirection::DOWN:
            return mapTileSize.y;
        case MoveDirection::LEFT:
        case MoveDirection::RIGHT:
            return mapTileSize.x;
        default:
            printf("NpcEntity.getTileSizeForDirection was given an invalid direction\n");
            return 0;
    }
}

void NpcEntity::roundPosition() {
    setPosition(std::round(getPosition().x), std::round(getPosition().y));
}

EntityCollidable NpcEntity::getEntityCollidable() {
    return this->entityCollidable;
}

//TODO: these probably belong in a utility class somewhere
int NpcEntity::getRandomIntInRange(int min, int max) {
    std::mt19937 eng(randomDevice());
    std::uniform_int_distribution<> distr(min, max); // define the range
    return distr(eng);
}

float NpcEntity::getRandomFloatInRange(float min, float max) {
    std::mt19937 eng(randomDevice());
    std::uniform_real_distribution<float> distr(min, max); // define the range
    return distr(eng);
}

//TODO: can this be moved to the header file?
//TODO: EVERYTHING needs to be multiples of  tile size, including the character textures (its frames). There should be a check to ensure this is happening so that I don't forget
void NpcEntity::initializeAnimations() {

    //TODO: these constants are temporary until I figure out where I want to load this information from. Probably from a more specific derived NpcEntity class
    entityAnimation.walkingAnimationDown.setSpriteSheet(*this->getTexture());
    entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(0, 0, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(ENTITY_WIDTH, 0, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(ENTITY_WIDTH*2, 0, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(ENTITY_WIDTH*3, 0, ENTITY_WIDTH, ENTITY_HEIGHT));

    entityAnimation.walkingAnimationRight.setSpriteSheet(*this->getTexture());
    entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(0, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(ENTITY_WIDTH, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(ENTITY_WIDTH*2, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(ENTITY_WIDTH*3, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));

    entityAnimation.walkingAnimationUp.setSpriteSheet(*this->getTexture());
    entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(0, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(ENTITY_WIDTH, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(ENTITY_WIDTH*2, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(ENTITY_WIDTH*3, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));

    entityAnimation.walkingAnimationLeft.setSpriteSheet(*this->getTexture());
    entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(0, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(ENTITY_WIDTH, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(ENTITY_WIDTH*2, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(ENTITY_WIDTH*3, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));

    entityAnimation.turnToFaceDirection(MoveDirection::DOWN);
}