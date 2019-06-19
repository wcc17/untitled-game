#ifndef NEWNEW_COLLIDABLEENTITY_H
#define NEWNEW_COLLIDABLEENTITY_H


#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../collisions/Collidable.h"

class CollidableEntity : public Collidable, public virtual sf::Sprite {
public:
    void fixPositionAfterCollision(const Collidable& collidedWith, MoveDirection entityDirection);
    sf::FloatRect getBoundingBox() const override;
};


#endif //NEWNEW_COLLIDABLEENTITY_H
