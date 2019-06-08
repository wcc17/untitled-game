#ifndef NEWNEW_PLAYER_H
#define NEWNEW_PLAYER_H


#include "../Entity.h"

class Player : public Entity {

public:
    Player(sf::Texture* texture, float windowWidth, float windowHeight);
protected:
    void initializeAnimations();
};


#endif //NEWNEW_PLAYER_H
