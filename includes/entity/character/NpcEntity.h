#ifndef NEWNEW_NPCENTITY_H
#define NEWNEW_NPCENTITY_H


#include "AnimatedEntity.h"
#include "MovableEntity.h"
#include "CollidableEntity.h"

class NpcEntity : public AnimatedEntity, public MovableEntity, public CollidableEntity {

public:
    void initialize(sf::Texture* texture, const Collidable& collidable);
    void update(sf::Time deltaTime);
protected:
    void initializeAnimations();
};


#endif //NEWNEW_NPCENTITY_H
