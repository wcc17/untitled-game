#include "../../../includes/entity/character/EntityAnimation.h"

void EntityAnimation::update(sf::Time deltaTime, MoveDirection direction) {
    move(direction);

    if(!animationPaused && currentAnimation) {
        currentTime += deltaTime;

        if(currentTime > frameTime) {
            //reset time, but keep the remainder for next time
            currentTime = sf::microseconds(currentTime.asMicroseconds() % frameTime.asMicroseconds());

            if( (currentFrame + 1) < (currentAnimation->getSize())) {
                currentFrame++;
            } else {
                currentFrame = 0;

                if(!shouldAnimationLoop) {
                    animationPaused = true;
                }
            }

            setTextureRectBasedOnCurrentFrame();
        }
    }
}

void EntityAnimation::move(MoveDirection direction) {
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

void EntityAnimation::turnToFaceEntityFacingDirection(MoveDirection facingDirection) {
    switch(facingDirection) {
        case MoveDirection::UP:
            EntityAnimation::faceDown();
            break;
        case MoveDirection::DOWN:
            EntityAnimation::faceUp();
            break;
        case MoveDirection::LEFT:
            EntityAnimation::faceRight();
            break;
        case MoveDirection::RIGHT:
            EntityAnimation::faceLeft();
            break;
        case MoveDirection::NONE:
            break;
    }

    currentFrame = 0;
    setTextureRectBasedOnCurrentFrame();
}

void EntityAnimation::turnToFaceDirection(MoveDirection faceDirection) {
    switch(faceDirection) {
        case MoveDirection::UP:
            EntityAnimation::faceUp();
            break;
        case MoveDirection::DOWN:
            EntityAnimation::faceDown();
            break;
        case MoveDirection::LEFT:
            EntityAnimation::faceLeft();
            break;
        case MoveDirection::RIGHT:
            EntityAnimation::faceRight();
            break;
        case MoveDirection::NONE:
            break;
    }

    currentFrame = 0;
    setTextureRectBasedOnCurrentFrame();
}

void EntityAnimation::setTextureRectBasedOnCurrentFrame() {
    if(currentAnimation) {
        textureRect = currentAnimation->getFrame(currentFrame);
    }
}

sf::IntRect EntityAnimation::getTextureRect() {
    return textureRect;
}

void EntityAnimation::playAnimation() {
    this->animationPaused = false;
}

void EntityAnimation::pauseAnimation() {
    this->animationPaused = true;
}

void EntityAnimation::stopAnimation() {
    this->pauseAnimation();
    this->currentFrame = 0;
    setTextureRectBasedOnCurrentFrame();
}

void EntityAnimation::moveUp() {
    faceUp();
    this->playAnimation();
}

void EntityAnimation::moveLeft() {
    faceLeft();
    this->playAnimation();
}

void EntityAnimation::moveDown() {
    faceDown();
    this->playAnimation();
}

void EntityAnimation::moveRight() {
    faceRight();
    this->playAnimation();
}

void EntityAnimation::faceUp() {
    this->currentAnimation = &walkingAnimationUp;
    setTextureRectBasedOnCurrentFrame();
}

void EntityAnimation::faceLeft() {
    this->currentAnimation = &walkingAnimationLeft;
    setTextureRectBasedOnCurrentFrame();
}

void EntityAnimation::faceDown() {
    this->currentAnimation = &walkingAnimationDown;
    setTextureRectBasedOnCurrentFrame();
}

void EntityAnimation::faceRight() {
    this->currentAnimation = &walkingAnimationRight;
    setTextureRectBasedOnCurrentFrame();
}

void EntityAnimation::stop() {
    this->stopAnimation();
}

void EntityAnimation::setFrameTime(sf::Time time) {
    this->frameTime = time;
}