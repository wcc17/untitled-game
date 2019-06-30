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

    //theres nothing changing the NpcEntity state right now
    /**
     * This can be interrupted at any time by player interacting with the npc
     *
     * 1. pick a random delay time between x and y seconds
     * 2. after that delay, toss a coin to decide whether to move or not
     * 3. If decided to move, choose a direction
     * 4. optional: If one direction is chosen, give weight to the other directions and reduce the weight for the chosen direction back to the default weight if applicable
     * 5. choose a distance at random (in multiples of mapTileSize) that keeps the entity inside of its move bounds
     */

    //TODO: this should be handled in Standing state instead of checking standing state manually
    if(state == STATE_STANDING) {
        this->moveDelay -= deltaTime;
        if (this->moveDelay <= sf::Time::Zero) {

            //choose 0 or 1 to decide whether to move.
            if (rand() % 2) { // TODO: wrap in its own function for clarity?. This isn't working properly yet

                MoveDirection moveDirection;
                //TODO: this is a function
                int direction = (rand() * 1.0 / RAND_MAX * 4) + 1;
                switch (direction) {
                    case 1:
                        moveDirection = MoveDirection::UP;
                        printf("npc moving up\n");
                        break;
                    case 2:
                        moveDirection = MoveDirection::DOWN;
                        printf("npc moving down\n");
                        break;
                    case 3:
                        moveDirection = MoveDirection::LEFT;
                        printf("npc moving left\n");
                        break;
                    case 4:
                        moveDirection = MoveDirection::RIGHT;
                        printf("npc moving right\n");
                        break;
                    default:
                        printf("Assigning an invalid direction in NpcEntity\n");
                        moveDirection = MoveDirection::NONE;
                        break;
                }


                //need to choose a random distance in multiple of mapTileSize in the chosen direction that keeps the entity within its bounds
                int maxDistance; //will be the furthest distance the entity can travel in the given direction
                int tileSize;
                switch (moveDirection) {
                    case MoveDirection::UP:
                        maxDistance = moveBoundaries.top;
                        maxDistance = getPosition().y - maxDistance;
                        tileSize = mapTileSize.y;
                        break;
                    case MoveDirection::DOWN:
                        maxDistance = moveBoundaries.top + moveBoundaries.height;
                        maxDistance -= getPosition().y;
                        tileSize = mapTileSize.y;
                        break;
                    case MoveDirection::LEFT:
                        maxDistance = moveBoundaries.left;
                        maxDistance = getPosition().x - maxDistance;
                        tileSize = mapTileSize.x;
                        break;
                    case MoveDirection::RIGHT:
                        maxDistance = moveBoundaries.left + moveBoundaries.width;
                        maxDistance -= getPosition().x;
                        tileSize = mapTileSize.x;
                        break;
                }

                printf("max distance: %i\n", maxDistance);

                if(maxDistance > 0) {
                    int distanceToMoveEntity = rand() % maxDistance + (tileSize * 2);
                    int remainder = distanceToMoveEntity % tileSize;

                    //make the distance the highest multiple of tileSize possible
                    if ((distanceToMoveEntity + (tileSize - remainder) < maxDistance)) {
                        distanceToMoveEntity += (tileSize - remainder);
                    } else {
                        distanceToMoveEntity -= remainder;
                    }

                    if (distanceToMoveEntity % tileSize != 0) {
                        printf("NpcEntity is trying to move in a distance that isn't a multiple of the tile size\n");
                    }

                    printf("wants to move with distance: %i\n", distanceToMoveEntity);

                    this->distanceToMove = distanceToMoveEntity;
                    this->state = STATE_MOVING;
                    this->currentDirection = moveDirection;
                }
            }
        }
    }
}

void NpcEntity::handleStandingState(sf::Time deltaTime) {
    CharacterEntity::handleStandingState(deltaTime);
    roundPosition();
}

void NpcEntity::handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    sf::Vector2f previousPosition = getPosition();
    CharacterEntity::handleMovingState(deltaTime, mapTileSize);
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
    }

    if(distanceMoved >= distanceToMove) {
        state = STATE_STANDING;
        currentDirection = MoveDirection::NONE;
        moveDelay = sf::seconds(3.f);
        distanceMoved = 0;
    }
}

void NpcEntity::handleInteractingState() {
    CharacterEntity::handleInteractingState();
}

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