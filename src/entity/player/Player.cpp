#include "../../../includes/entity/player/Player.h"

const float PLAYER_WIDTH = 16.f;
const float PLAYER_HEIGHT = 24.f;
const float PLAYER_FRAME_TIME = 0.16f;
const float MOVEMENT_SPEED = 80.f;

void Player::initialize(sf::Texture* texture, std::string collidableName, CollidableType collidableType, sf::FloatRect initialBoundingBox) {
    AnimatedEntity::initialize(texture);
    MovableEntity::initialize(MOVEMENT_SPEED);
    this->name = collidableName;
    this->type = collidableType;

    this->setPosition(sf::Vector2f(initialBoundingBox.left, initialBoundingBox.top));
    this->setFrameTime(sf::seconds(PLAYER_FRAME_TIME));
    initializeAnimations();
}

void Player::move(sf::Time deltaTime, MoveDirection direction, sf::Vector2u mapTileSize, sf::Vector2u mapSizeInPixels) {
    MovableEntity::move(deltaTime, direction, mapTileSize, mapSizeInPixels);
    AnimatedEntity::move(currentDirection);
}

void Player::update(sf::Time deltaTime) {
    updateBoundingBox(this->getGlobalBounds());
    AnimatedEntity::update(deltaTime);
    MovableEntity::update(deltaTime);
}

void Player::initializeAnimations() {
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
    updateBoundingBox(this->getGlobalBounds());
}