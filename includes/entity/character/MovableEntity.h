#ifndef NEWNEW_MOVABLEENTITY_H
#define NEWNEW_MOVABLEENTITY_H


#include <SFML/System.hpp>
#include "../../controller/MoveDirection.h"
#include "../character/EntityState.h"

class MovableEntity {
public:
    void initialize(float moveSpeed);
    void update(sf::Time deltaTime);
    void onMoveEvent(MoveDirection direction);
    sf::Vector2f getMovement();

protected:
    sf::Vector2f movement;
    MoveDirection currentDirection;

private:
    void resetMovement();
    float moveSpeed;
    EntityState state;
};


#endif //NEWNEW_MOVABLEENTITY_H
