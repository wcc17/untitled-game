#ifndef NEWNEW_MONSTERNPCENTITY_H
#define NEWNEW_MONSTERNPCENTITY_H

#include "../NpcEntity.h"

class MonsterNpcEntity : public NpcEntity {

protected:
    //TODO: EVERYTHING needs to be multiples of  tile size, including the character textures (its frames). There should be a check to ensure this is happening so that I don't forget
    void initializeAnimations() override {

        this->entitySpeed = 70.f;
        this->entityFrameTime = 0.16f;

        entityAnimation.walkingAnimationDown.setSpriteSheet(*this->getTexture());
        entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(0, 0, entityWidth, entityHeight));
        entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(entityWidth, 0, entityWidth, entityHeight));
        entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(entityWidth*2, 0, entityWidth, entityHeight));
        entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(entityWidth*3, 0, entityWidth, entityHeight));

        entityAnimation.walkingAnimationRight.setSpriteSheet(*this->getTexture());
        entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(0, entityHeight, entityWidth, entityHeight));
        entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(entityWidth, entityHeight, entityWidth, entityHeight));
        entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(entityWidth*2, entityHeight, entityWidth, entityHeight));
        entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(entityWidth*3, entityHeight, entityWidth, entityHeight));

        entityAnimation.walkingAnimationUp.setSpriteSheet(*this->getTexture());
        entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(0, entityHeight*2, entityWidth, entityHeight));
        entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(entityWidth, entityHeight*2, entityWidth, entityHeight));
        entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(entityWidth*2, entityHeight*2, entityWidth, entityHeight));
        entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(entityWidth*3, entityHeight*2, entityWidth, entityHeight));

        entityAnimation.walkingAnimationLeft.setSpriteSheet(*this->getTexture());
        entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(0, entityHeight*3, entityWidth, entityHeight));
        entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(entityWidth, entityHeight*3, entityWidth, entityHeight));
        entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(entityWidth*2, entityHeight*3, entityWidth, entityHeight));
        entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(entityWidth*3, entityHeight*3, entityWidth, entityHeight));

        entityAnimation.turnToFaceDirection(MoveDirection::DOWN);
    }
};

#endif //NEWNEW_MONSTERNPCENTITY_H
