#ifndef NEWNEW_ENTITY_H
#define NEWNEW_ENTITY_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include "Animation.h"

class Entity : public sf::Sprite {

public:
    Entity(sf::Texture* texture);
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

    //TODO: should probably refactor animation stuff into its own class that inherits entity once its working
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


#endif //NEWNEW_ENTITY_H
