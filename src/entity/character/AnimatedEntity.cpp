#include "../../../includes/entity/character/AnimatedEntity.h"

void AnimatedEntity::initialize(sf::Texture* texture) {
    this->setTexture(*texture);
}

void AnimatedEntity::update(sf::Time deltaTime, MoveDirection direction) {
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

void AnimatedEntity::move(MoveDirection direction) {
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

void AnimatedEntity::setTextureRectBasedOnCurrentFrame() {
    if(currentAnimation) {
        sf::IntRect rect = currentAnimation->getFrame(currentFrame);
        setTextureRect(rect);
    }
}

void AnimatedEntity::playAnimation() {
    this->animationPaused = false;
}

void AnimatedEntity::pauseAnimation() {
    this->animationPaused = true;
}

void AnimatedEntity::stopAnimation() {
    this->pauseAnimation();
    this->currentFrame = 0;
    setTextureRectBasedOnCurrentFrame();
}

void AnimatedEntity::moveUp() {
    this->playAnimation();
    this->currentAnimation = &walkingAnimationUp;
}

void AnimatedEntity::moveLeft() {
    this->playAnimation();
    this->currentAnimation = &walkingAnimationLeft;
}

void AnimatedEntity::moveDown() {
    this->playAnimation();
    this->currentAnimation = &walkingAnimationDown;
}

void AnimatedEntity::moveRight() {
    this->playAnimation();
    this->currentAnimation = &walkingAnimationRight;
}

void AnimatedEntity::stop() {
    this->stopAnimation();
}

void AnimatedEntity::setFrameTime(sf::Time time) {
    this->frameTime = time;
}