#ifndef NEWNEW_COLLIDABLE_H
#define NEWNEW_COLLIDABLE_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "CollidableType.h"

class Collidable {
public:
    Collidable();
    Collidable(std::string name, CollidableType type, sf::Vector2f position, sf::Vector2f size);
    sf::Vector2f getFixedPositionAfterCollision(sf::FloatRect entityRect, sf::FloatRect otherRect, sf::Vector2f movement);
    void updateBoundingBox(sf::FloatRect newBounds);
    CollidableType getType();
    std::string getName();
    sf::FloatRect getBoundingBox();
protected:
    std::string name;
    CollidableType type;
    sf::FloatRect boundingBox;
};


#endif //NEWNEW_COLLIDABLE_H
