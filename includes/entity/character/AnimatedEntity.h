#ifndef NEWNEW_ANIMATEDENTITY_H
#define NEWNEW_ANIMATEDENTITY_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Animation.h"
#include "../../collisions/Collidable.h"

class AnimatedEntity : public sf::Sprite, public Collidable {

public:
    void initialize(sf::Texture *texture, std::string name, CollidableType collidableType);
    void update(sf::Time deltaTime);
    void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
    void stop();

protected:
    virtual void initializeAnimations() {};
    void setFrameTime(sf::Time time);
    sf::Vector2i getWidthOfEntityForCurrentFrame();
    Animation* currentAnimation;
    Animation walkingAnimationDown;
    Animation walkingAnimationLeft;
    Animation walkingAnimationRight;
    Animation walkingAnimationUp;

private:
    void playAnimation();
    void pauseAnimation();
    void stopAnimation();
    void setTextureRectBasedOnCurrentFrame();
    void updateBoundingBox();
    sf::Time frameTime;
    sf::Time currentTime;
    bool animationPaused = false;
    bool shouldAnimationLoop = true; //TODO: should be able to pass this value to the entity
    int currentFrame = 0;
};


#endif //NEWNEW_ANIMATEDENTITY_H
