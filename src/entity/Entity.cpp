#include "../../includes/entity/Entity.h"

Entity::Entity(sf::Texture *texture) : frameTime(sf::seconds(0.f)), currentTime(sf::seconds(0.f)) {
    this->setTexture(*texture);

    //TODO: need a better way to set the scale. other sprites will need to have the same scale. also if the window is resized, the scale has to change too
    this->scale(sf::Vector2f(5.f, 5.f));
}

void Entity::update(sf::Time deltaTime) {
    if(!animationPaused && currentAnimation) {
        currentTime += deltaTime;

        if(currentTime > frameTime) {
            //reset time, but keep the remainder
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

void Entity::setTextureRectBasedOnCurrentFrame() {
    if(currentAnimation) {
        sf::IntRect rect = currentAnimation->getFrame(currentFrame);
        setTextureRect(rect);
    }
}

void Entity::playAnimation() {
    this->animationPaused = false;
}

void Entity::pauseAnimation() {
    this->animationPaused = true;
}

void Entity::stopAnimation() {
    this->pauseAnimation();
    this->currentFrame = 0;
    setTextureRectBasedOnCurrentFrame();
}

void Entity::moveUp() {
    this->playAnimation();
    this->currentAnimation = &walkingAnimationUp;
}

void Entity::moveLeft() {
    this->playAnimation();
    this->currentAnimation = &walkingAnimationLeft;
}

void Entity::moveDown() {
    this->playAnimation();
    this->currentAnimation = &walkingAnimationDown;
}

void Entity::moveRight() {
    this->playAnimation();
    this->currentAnimation = &walkingAnimationRight;
}

void Entity::stop() {
    this->stopAnimation();
}

void Entity::setFrameTime(sf::Time time) {
    this->frameTime = time;
}