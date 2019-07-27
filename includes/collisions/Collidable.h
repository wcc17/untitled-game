#ifndef NEWNEW_COLLIDABLE_H
#define NEWNEW_COLLIDABLE_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "../map/ObjectType.h"
#include "../controller/MoveDirection.h"

class Collidable {
public:
    Collidable();
    Collidable(std::string name, ObjectType type, sf::Vector2f position, sf::Vector2f size);
    ObjectType getType() const;
    void setType(ObjectType type);
    std::string getName() const;
    void setName(std::string name);
    sf::FloatRect getBoundingBox() const;
    void setBoundingBox(sf::FloatRect boundingBox);

private:
    std::string name;
    ObjectType type;
    sf::FloatRect boundingBox;

};


#endif //NEWNEW_COLLIDABLE_H
