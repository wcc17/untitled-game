#ifndef NEWNEW_COLLIDABLE_H
#define NEWNEW_COLLIDABLE_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "CollidableType.h"

class Collidable {
public:
    Collidable(sf::Vector2f position, sf::Vector2f size, std::string name, CollidableType type);
    CollidableType getType();
    sf::FloatRect getBoundingBox();
protected:
    sf::FloatRect boundingBox;
    std::string collidableName;
    CollidableType type;
};


#endif //NEWNEW_COLLIDABLE_H
