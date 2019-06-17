#ifndef NEWNEW_MOVABLEENTITY_H
#define NEWNEW_MOVABLEENTITY_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../controller/MoveDirection.h"
#include "../character/EntityState.h"

class MovableEntity : virtual public sf::Sprite {
public:
    void initialize(float moveSpeed);
    void update(sf::Time deltaTime);
    void move(sf::Time deltaTime, MoveDirection direction, sf::Vector2u mapTileSize, sf::Vector2u mapSizeInPixels);
    sf::Vector2f getMovement();

protected:
    sf::Vector2f movement;
    MoveDirection currentDirection;

private:
    void setRegularMovement();
    void setGoalLimitedMovement(sf::Time deltaTime, sf::Vector2u mapTileSize, sf::Vector2u mapSizeInPixels);
    void handleStandingState(MoveDirection direction);
    void handleMovingState(MoveDirection direction, sf::Time deltaTime, sf::Vector2u mapTileSize, sf::Vector2u mapSizeInPixels);
    void handleMovingToGoalState(MoveDirection direction, sf::Time deltaTime, sf::Vector2u mapTileSize, sf::Vector2u mapSizeInPixels);
    bool movementGoalReached(sf::Time deltaTime, sf::Vector2u mapTileSize, sf::Vector2u mapSizeInPixels);
    void resetMovement();
    MoveDirection previousDirection;
    float moveSpeed;
    EntityState state;
};


#endif //NEWNEW_MOVABLEENTITY_H
