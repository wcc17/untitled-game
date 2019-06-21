#ifndef NEWNEW_CHARACTERENTITY_H
#define NEWNEW_CHARACTERENTITY_H


#include "MovableEntity.h"
#include "CollidableEntity.h"
#include "AnimatedEntity.h"

class CharacterEntity : public AnimatedEntity, public MovableEntity, public CollidableEntity {
public:
    void initialize(sf::Texture* texture, float movementSpeed, const Collidable& collidable, float FrameTime);
    void roundPosition();
private:

};


#endif //NEWNEW_CHARACTERENTITY_H
