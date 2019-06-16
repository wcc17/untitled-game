#ifndef NEWNEW_NPCENTITY_H
#define NEWNEW_NPCENTITY_H


#include "AnimatedEntity.h"
#include "MovableEntity.h"

class NpcEntity : public AnimatedEntity, public MovableEntity, public Collidable {

public:
    void initialize(sf::Texture* texture, std::string npcName, CollidableType collidableType, sf::FloatRect bounds);
    void update(sf::Time deltaTime);
protected:
    void initializeAnimations();
};


#endif //NEWNEW_NPCENTITY_H
