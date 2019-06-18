#ifndef NEWNEW_MOVABLEENTITY_H
#define NEWNEW_MOVABLEENTITY_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../controller/MoveDirection.h"
#include "../character/EntityState.h"

class MovableEntity : virtual public sf::Sprite {
public:
    void initialize(float moveSpeed);
    void move(sf::Time deltaTime, MoveDirection direction, sf::Vector2u mapTileSize);
    sf::Vector2f getFixedPositionAfterCollision(sf::FloatRect entityRect, sf::FloatRect otherRect, MoveDirection direction);
    MoveDirection getCurrentDirection();

protected:
    MoveDirection currentDirection;

private:
    void handleStandingState(MoveDirection direction, sf::Time deltaTime);
    void handleMovingState(MoveDirection direction, sf::Time deltaTime, sf::Vector2u mapTileSize);

    sf::Vector2f getRegularMovement(float speed);
    sf::Vector2f getGoalLimitedMovement(sf::Time deltaTime, sf::Vector2u mapTileSize);
    bool movementGoalReached(sf::Vector2u mapTileSize);
    void performRegularMove(sf::Time deltaTime);
    void performGoalLimitedMove(sf::Time deltaTime, sf::Vector2u mapTileSize);

    static int getTileSizeForDirection(MoveDirection direction, sf::Vector2u mapTileSize);
    static int getChangingPosition(MoveDirection direction, sf::Vector2f position);

    MoveDirection previousDirection;
    float moveSpeed;
    EntityState state;
};


#endif //NEWNEW_MOVABLEENTITY_H
