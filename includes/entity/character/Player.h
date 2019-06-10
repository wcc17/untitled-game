#ifndef NEWNEW_PLAYER_H
#define NEWNEW_PLAYER_H


#include "AnimatedEntity.h"

class Player : public AnimatedEntity {

public:
    void initialize(sf::Texture* texture, float windowWidth, float windowHeight);
    void update(sf::Time deltaTime, sf::Vector2f viewCenter);
protected:
    void initializeAnimations();
};


#endif //NEWNEW_PLAYER_H
