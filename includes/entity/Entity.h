#ifndef NEWNEW_ENTITY_H
#define NEWNEW_ENTITY_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

class Entity {

public:
    virtual void update(sf::Time deltaTime) = 0;
    virtual void moveUp() = 0;
    virtual void moveLeft() = 0;
    virtual void moveDown() = 0;
    virtual void moveRight() = 0;
    virtual void stop() = 0;
};


#endif //NEWNEW_ENTITY_H
