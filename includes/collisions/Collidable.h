#ifndef NEWNEW_COLLIDABLE_H
#define NEWNEW_COLLIDABLE_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "CollidableType.h"
#include "../controller/MoveDirection.h"

class Collidable {
public:
    Collidable();
    Collidable(std::string name, CollidableType type, sf::Vector2f position, sf::Vector2f size);
    CollidableType getType() const;
    std::string getName() const;
    virtual sf::FloatRect getBoundingBox() const;
protected:
    std::string name;
    CollidableType type;
private:
    sf::FloatRect boundingBox;

};


#endif //NEWNEW_COLLIDABLE_H
