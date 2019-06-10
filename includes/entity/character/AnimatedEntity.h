#ifndef NEWNEW_ANIMATEDENTITY_H
#define NEWNEW_ANIMATEDENTITY_H

#include <SFML/System/Time.hpp>
#include "Animation.h"
#include "../Entity.h"

class AnimatedEntity : public Entity, public sf::Sprite {

public:
    void initialize(sf::Texture *texture);
    void update(sf::Time deltaTime);
    void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
    void stop();

protected:
    virtual void initializeAnimations() {};

    void setFrameTime(sf::Time time);
    void playAnimation();
    void pauseAnimation();
    void stopAnimation();
    void setTextureRectBasedOnCurrentFrame();

    Animation* currentAnimation;
    Animation walkingAnimationDown;
    Animation walkingAnimationLeft;
    Animation walkingAnimationRight;
    Animation walkingAnimationUp;

    sf::Time frameTime;
    sf::Time currentTime;
    bool animationPaused = false;
    bool shouldAnimationLoop = true; //TODO: should be able to pass this value to the entity
    int currentFrame = 0;

};


#endif //NEWNEW_ANIMATEDENTITY_H
