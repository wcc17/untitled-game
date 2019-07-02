#include "../../../includes/entity/character/NpcEntity.h"

//TODO: these will be moved out once there are different entities being loaded
const float ENTITY_WIDTH = 16.f;
const float ENTITY_HEIGHT = 24.f;
const float ENTITY_MOVEMENT_SPEED = 65.f;
const float ENTITY_FRAME_TIME = 0.16f; //TODO: not sure where I want to load this from yet

const sf::Vector2f moveDelayRange = sf::Vector2f(1.5f, 5.5f);

void NpcEntity::initialize(sf::Texture* texture, const Collidable& collidable, sf::IntRect moveBoundaries) {
    srand(time(NULL)); //TODO: should this be done somewhere else? will likely need rand() somewhere else

    CharacterEntity::initialize(texture, ENTITY_MOVEMENT_SPEED, collidable, ENTITY_FRAME_TIME);
    this->moveBoundaries = moveBoundaries;
    this->moveDelay = sf::seconds(3.f); //TODO: should be chosen randomly
}

void NpcEntity::update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    CharacterEntity::update(deltaTime, mapTileSize);
}

void NpcEntity::handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    CharacterEntity::handleStandingState(deltaTime, mapTileSize);
    roundPosition();

    if(moveDelayTimerDone(deltaTime)) {
        setupEntityMovement(mapTileSize);
    }
}

void NpcEntity::handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    sf::Vector2f previousPosition = getPosition();
    CharacterEntity::handleMovingState(deltaTime, mapTileSize);
    roundPosition();

    moveEntityTowardMovementGoal(previousPosition);
}

void NpcEntity::handleInteractingState() {
    CharacterEntity::handleInteractingState();
}

//TODO: should this be an AnimatedEntity method? turnToFaceEntityFacingDirection that takes facingDirection as argument
void NpcEntity::turnToFacePlayer(MoveDirection playerFacingDirection) {
    switch(playerFacingDirection) {
        case MoveDirection::UP:
            AnimatedEntity::faceDown();
            break;
        case MoveDirection::DOWN:
            AnimatedEntity::faceUp();
            break;
        case MoveDirection::LEFT:
            AnimatedEntity::faceRight();
            break;
        case MoveDirection::RIGHT:
            AnimatedEntity::faceLeft();
            break;
        case MoveDirection::NONE:
            break;
    }
}

bool NpcEntity::moveDelayTimerDone(sf::Time deltaTime) {
    this->moveDelay -= deltaTime;
    if (this->moveDelay <= sf::Time::Zero) {
        this->moveDelay = sf::seconds(3.f);
        return true;
    }

    return false;
}

void NpcEntity::setupEntityMovement(const sf::Vector2u& mapTileSize) {
    if (flipCoin()) {

        //TODO: this should be decided in its own function with weighted odds for directions that haven't been travelled recently. The next 3-4 lines should be in the function
        int randomDirection = (rand() * 1.0 / RAND_MAX * 4) + 1;
        if(randomDirection > 4 || randomDirection < 1) {
            randomDirection = 0;
        }

        MoveDirection moveDirection = static_cast<MoveDirection>(randomDirection);
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

//TODO: I think the random related functions would be better in a util class or something like that. There will be more once move delay timer and direction are weighted differently based on previous
bool NpcEntity::flipCoin() {
    return rand() % 2 == 1;
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
            printf("Assigning an invalid direction in NpcEntity\n");
            maxDistanceEntityCanTravel = 0;
            break;
    }

    printf("max distance: %i\n", maxDistanceEntityCanTravel);
    return maxDistanceEntityCanTravel;
}

//TODO: can be static?
int NpcEntity::determineRandomDistanceToMoveEntity(int maxDistanceEntityCanTravel, int tileSize) {
    int distanceToMoveEntity = rand() % maxDistanceEntityCanTravel + (tileSize * 2);
    int remainder = distanceToMoveEntity % tileSize;

    //make the distance the highest multiple of tileSize possible
    if ((distanceToMoveEntity + (tileSize - remainder) < maxDistanceEntityCanTravel)) {
        distanceToMoveEntity += (tileSize - remainder);
    } else {
        distanceToMoveEntity -= remainder;
    }

    if (distanceToMoveEntity % tileSize != 0) {
        //TODO: should I exit from the caller method when this happens?
        printf("NpcEntity is trying to move in a distance that isn't a multiple of the tile size\n");
    }

    printf("is going to move with distance: %i\n", distanceToMoveEntity);
    return distanceToMoveEntity;
}

//TODO: can be static
int NpcEntity::getTileSizeForDirection(MoveDirection moveDirection, const sf::Vector2u& mapTileSize) {
    switch (moveDirection) {
        case MoveDirection::UP:
        case MoveDirection::DOWN:
            return mapTileSize.y;
        case MoveDirection::LEFT:
        case MoveDirection::RIGHT:
            return mapTileSize.x;
        default:
            //TODO: should I exit from the caller method when this happens?
            printf("NpcEntity.getTileSizeForDirection was given an invalid direction\n");
            return 0;
    }
}

void NpcEntity::moveEntityTowardMovementGoal(sf::Vector2f previousPosition) {
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
    }

    if(distanceMoved >= movementGoal) {
        state = STATE_STANDING;
        currentDirection = MoveDirection::NONE;
        distanceMoved = 0;
    }
}



//TODO: EVERYTHING needs to be multiples of  tile size, including the character textures (its frames). There should be a check to ensure this is happening so that I don't forget
void NpcEntity::initializeAnimations() {

    //TODO: these constants are temporary until I figure out where I want to load this information from. Probably from a more specific derived NpcEntity class
    walkingAnimationDown.setSpriteSheet(*this->getTexture());
    walkingAnimationDown.addFrame(sf::IntRect(0, 0, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationDown.addFrame(sf::IntRect(ENTITY_WIDTH, 0, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationDown.addFrame(sf::IntRect(ENTITY_WIDTH*2, 0, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationDown.addFrame(sf::IntRect(ENTITY_WIDTH*3, 0, ENTITY_WIDTH, ENTITY_HEIGHT));

    walkingAnimationRight.setSpriteSheet(*this->getTexture());
    walkingAnimationRight.addFrame(sf::IntRect(0, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationRight.addFrame(sf::IntRect(ENTITY_WIDTH, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationRight.addFrame(sf::IntRect(ENTITY_WIDTH*2, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationRight.addFrame(sf::IntRect(ENTITY_WIDTH*3, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));

    walkingAnimationUp.setSpriteSheet(*this->getTexture());
    walkingAnimationUp.addFrame(sf::IntRect(0, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationUp.addFrame(sf::IntRect(ENTITY_WIDTH, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationUp.addFrame(sf::IntRect(ENTITY_WIDTH*2, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationUp.addFrame(sf::IntRect(ENTITY_WIDTH*3, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));

    walkingAnimationLeft.setSpriteSheet(*this->getTexture());
    walkingAnimationLeft.addFrame(sf::IntRect(0, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationLeft.addFrame(sf::IntRect(ENTITY_WIDTH, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationLeft.addFrame(sf::IntRect(ENTITY_WIDTH*2, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationLeft.addFrame(sf::IntRect(ENTITY_WIDTH*3, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));

    this->currentAnimation = &walkingAnimationDown;
    setTextureRectBasedOnCurrentFrame();
}