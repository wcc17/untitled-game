#ifndef NEWNEW_COLLIDABLE_H
#define NEWNEW_COLLIDABLE_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "CollidableType.h"

class Collidable {
public:
    Collidable();
    Collidable(std::string name, CollidableType type, sf::Vector2f position, sf::Vector2f size);
    CollidableType getType();
    std::string getName();
    virtual sf::FloatRect getBoundingBox();
protected:
    std::string name;
    CollidableType type;
    sf::FloatRect boundingBox;
};


#endif //NEWNEW_COLLIDABLE_H
