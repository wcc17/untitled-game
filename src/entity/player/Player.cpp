#include "../../../includes/entity/player/Player.h"

const float PLAYER_WIDTH = 16.f;
const float PLAYER_HEIGHT = 26.f;
const float PLAYER_FRAME_TIME = 0.16f;

void Player::initialize(sf::Texture* texture, std::string collidableName, CollidableType type, sf::FloatRect initialBoundingBox) {
    AnimatedEntity::initialize(texture, collidableName, type);

    this->setPosition(initialBoundingBox.left, initialBoundingBox.top);
//    this->setPosition( (960 / 2) - ((getBoundingBox().width /4) / 2), (540 / 2) - ((getBoundingBox().height /4) / 2));
//    this->setPosition( (windowWidth / 2) - ((getBoundingBox().width /4) / 2), (windowHeight / 2) - ((getBoundingBox().height /4) / 2));
    this->setFrameTime(sf::seconds(PLAYER_FRAME_TIME));
    initializeAnimations();
}

void Player::update(sf::Time deltaTime) {
    AnimatedEntity::update(deltaTime);
}

void Player::onControllerMoveEvent(MoveDirection direction) {
    switch(direction) {
        case MoveDirection::UP:
            moveUp();
            break;
        case MoveDirection::LEFT:
            moveLeft();
            break;
        case MoveDirection::DOWN:
            moveDown();
            break;
        case MoveDirection::RIGHT:
            moveRight();
            break;
        case MoveDirection::NONE:
            stop();
            break;
        default:
            break;
    }
}

void Player::setPlayerPositionFromViewCenter(sf::Vector2f viewCenter) {
    float newPlayerX = viewCenter.x - (getWidthOfEntityForCurrentFrame().x / 2);
    float newPlayerY = viewCenter.y - (getWidthOfEntityForCurrentFrame().y / 2);
    setPosition(newPlayerX, newPlayerY);
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
    updateBoundingBox();
}