#ifndef NEWNEW_ENTITYANIMATION_H
#define NEWNEW_ENTITYANIMATION_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Animation.h"
#include "../../collisions/Collidable.h"
#include "../../controller/MoveDirection.h"
#include <cmath>

class EntityAnimation {

public:
    void initialize(sf::Texture *texture);
    void update(sf::Time deltaTime, MoveDirection direction);
    void stop();
    void setFrameTime(sf::Time time);
    void turnToFaceEntityFacingDirection(MoveDirection facingDirection);
    void turnToFaceDirection(MoveDirection faceDirection);
    sf::IntRect getTextureRect();
    Animation walkingAnimationDown;
    Animation walkingAnimationLeft;
    Animation walkingAnimationRight;
    Animation walkingAnimationUp;

protected:
    virtual void initializeAnimations() {};
    void setTextureRectBasedOnCurrentFrame();
    Animation* currentAnimation;

private:
    void move(MoveDirection direction);
    void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
    void faceUp();
    void faceLeft();
    void faceDown();
    void faceRight();
    void playAnimation();
    void pauseAnimation();
    void stopAnimation();
    sf::IntRect textureRect;
    sf::Time frameTime;
    sf::Time currentTime;
    bool animationPaused = false;
    bool shouldAnimationLoop = true; //TODO: should be able to pass this value to the entity
    int currentFrame = 0;
};


#endif //NEWNEW_ENTITYANIMATION_H
