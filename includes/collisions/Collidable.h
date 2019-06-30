#ifndef NEWNEW_COLLIDABLE_H
#define NEWNEW_COLLIDABLE_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "../scene/ObjectType.h"
#include "../controller/MoveDirection.h"

class Collidable {
public:
    Collidable();
    Collidable(std::string name, ObjectType type, sf::Vector2f position, sf::Vector2f size);
    ObjectType getType() const;
    std::string getName() const;
    virtual sf::FloatRect getBoundingBox() const;
protected:
    std::string name;
    ObjectType type;
private:
    sf::FloatRect boundingBox;

};


#endif //NEWNEW_COLLIDABLE_H
