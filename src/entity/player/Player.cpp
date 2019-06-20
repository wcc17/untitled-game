#include "../../../includes/entity/player/Player.h"

const float PLAYER_WIDTH = 16.f;
const float PLAYER_HEIGHT = 24.f;
const float PLAYER_FRAME_TIME = 0.16f;
const float MOVEMENT_SPEED = 80.f;
const float VICINITY_BOUNDS_OFFSET = 4.f;

void Player::initialize(sf::Texture* texture, const Collidable& collidable) {
    AnimatedEntity::initialize(texture);
    MovableEntity::initialize(MOVEMENT_SPEED);

    this->name = collidable.getName();
    this->type = collidable.getType();
    this->setPosition(sf::Vector2f(collidable.getBoundingBox().left, collidable.getBoundingBox().top));

    this->setFrameTime(sf::seconds(PLAYER_FRAME_TIME));
    initializeAnimations();
}

void Player::update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    MovableEntity::update(deltaTime, mapTileSize);
    AnimatedEntity::update(deltaTime, currentDirection);
}

void Player::fixPositionAfterCollision(const Collidable& collidedWith) {
    CollidableEntity::fixPositionAfterCollision(collidedWith, currentDirection);
}

//TODO: this should be in a class shared by NpcEntity and Player. MovableEntity or the CharacterEntity I'm planning on?
//TODO: roundPosition can be called in NpcEntity's update function. Player does not have that luxury
void Player::roundPosition() {
    setPosition(std::round(getPosition().x), std::round(getPosition().y));
}

//TODO: this should be in CollidableEntity, not in Player
sf::FloatRect Player::getVicinityBounds() const {
    sf::FloatRect vicinityBounds = sf::FloatRect(getGlobalBounds().left - VICINITY_BOUNDS_OFFSET,
                                                 getGlobalBounds().top - VICINITY_BOUNDS_OFFSET,
                                                 getGlobalBounds().width + (VICINITY_BOUNDS_OFFSET*2),
                                                 getGlobalBounds().height + (VICINITY_BOUNDS_OFFSET*2));
    return vicinityBounds;
}

void Player::initializeAnimations() {
//TODO: EVERYTHING needs to be multiples of  tile size, including the character textures (its frames). Should there be a check to ensure this is happening so that I don't forget? How can I get the tile size here? Also NpcEntity
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