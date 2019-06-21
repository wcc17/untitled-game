#include "../../../includes/entity/player/Player.h"

const float PLAYER_WIDTH = 16.f;
const float PLAYER_HEIGHT = 24.f;
const float PLAYER_FRAME_TIME =  0.16f;
const float MOVEMENT_SPEED = 80.f;
const int VICINITY_BOUNDS_OFFSET = 4;

void Player::initialize(sf::Texture* texture, const Collidable& collidable) {
    CharacterEntity::initialize(texture, MOVEMENT_SPEED, collidable, PLAYER_FRAME_TIME);
    this->setVicinityBoundsOffset(VICINITY_BOUNDS_OFFSET);
}

//TODO: MovableEntity and AnimatedEntity code to CharacterEntity
void Player::update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    handleActionButtonPressed();
    MovableEntity::update(deltaTime, mapTileSize);
    AnimatedEntity::update(deltaTime, currentDirection);
    resetAfterFrame();
}

//TODO: MovableEntity and AnimatedEntity code to CharacterEntity
void Player::fixPositionAfterCollision(const Collidable& collidedWith) {
    CollidableEntity::fixPositionAfterCollision(collidedWith, currentDirection);
}

void Player::handleActionButtonPressed() {
    if(actionButtonPressed) {
        for(std::shared_ptr<Collidable> collidable : collidablesInVicinity) {

            MoveDirection currentlyFacingDirection = MovableEntity::getCurrentFacingDirection();
            if(CollidableEntity::isFacingCollidableInVicinity(currentlyFacingDirection, *collidable)) {
                printf("Player is interacting with %s\n", collidable->getName().c_str());
            }
        }
    }
}

void Player::setActionButtonPressed() {
    actionButtonPressed = true;
}

void Player::initializeAnimations() {
    //TODO: EVERYTHING needs to be multiples of tile size, including the character textures (its frames). Should there be a check to ensure this is happening so that I don't forget? How can I get the tile size here? Also NpcEntity
    walkingAnimationDown.setSpriteSheet(*this->getTexture());
    walkingAnimationDown.addFrame(sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationDown.addFrame(sf::IntRect(PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationDown.addFrame(sf::IntRect(PLAYER_WIDTH*2, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationDown.addFrame(sf::IntRect(PLAYER_WIDTH*3, 0, PLAYER_WIDTH, PLAYER_HEIGHT));

    walkingAnimationRight.setSpriteSheet(*this->getTexture());
    walkingAnimationRight.addFrame(sf::IntRect(0, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationRight.addFrame(sf::IntRect(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationRight.addFrame(sf::IntRect(PLAYER_WIDTH*2, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationRight.addFrame(sf::IntRect(PLAYER_WIDTH*3, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));

    walkingAnimationUp.setSpriteSheet(*this->getTexture());
    walkingAnimationUp.addFrame(sf::IntRect(0, PLAYER_HEIGHT*2, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationUp.addFrame(sf::IntRect(PLAYER_WIDTH, PLAYER_HEIGHT*2, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationUp.addFrame(sf::IntRect(PLAYER_WIDTH*2, PLAYER_HEIGHT*2, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationUp.addFrame(sf::IntRect(PLAYER_WIDTH*3, PLAYER_HEIGHT*2, PLAYER_WIDTH, PLAYER_HEIGHT));

    walkingAnimationLeft.setSpriteSheet(*this->getTexture());
    walkingAnimationLeft.addFrame(sf::IntRect(0, PLAYER_HEIGHT*3, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationLeft.addFrame(sf::IntRect(PLAYER_WIDTH, PLAYER_HEIGHT*3, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationLeft.addFrame(sf::IntRect(PLAYER_WIDTH*2, PLAYER_HEIGHT*3, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationLeft.addFrame(sf::IntRect(PLAYER_WIDTH*3, PLAYER_HEIGHT*3, PLAYER_WIDTH, PLAYER_HEIGHT));

    this->currentAnimation = &walkingAnimationDown;
    setTextureRectBasedOnCurrentFrame();
}

void Player::resetAfterFrame() {
    CollidableEntity::clearCollidablesInVicinity();
    actionButtonPressed = false;
}