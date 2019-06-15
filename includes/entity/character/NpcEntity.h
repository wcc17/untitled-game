#ifndef NEWNEW_NPCENTITY_H
#define NEWNEW_NPCENTITY_H


#include "AnimatedEntity.h"

class NpcEntity : public AnimatedEntity {

public:
    void initialize(sf::Texture* texture);
    void update(sf::Time deltaTime);
protected:
    void initializeAnimations();
};


#endif //NEWNEW_NPCENTITY_H
