#ifndef NEWNEW_MOVABLEENTITY_H
#define NEWNEW_MOVABLEENTITY_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../controller/MoveDirection.h"
#include "../character/EntityState.h"

class MovableEntity : virtual public sf::Sprite {
public:
    void initialize(float moveSpeed);
    void handleStandingState(sf::Time deltaTime, EntityState& state);
    void handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize, EntityState& state);
    MoveDirection getCurrentDirection();
    void setCurrentDirection(MoveDirection direction);

protected:
    MoveDirection getCurrentFacingDirection();
    MoveDirection currentDirection;

private:
    sf::Vector2f getRegularMovement(float speed);
    sf::Vector2f getGoalLimitedMovement(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    bool movementGoalReached(const sf::Vector2u& mapTileSize);
    void performRegularMove(sf::Time deltaTime);
    void performGoalLimitedMove(sf::Time deltaTime, const sf::Vector2u& mapTileSize);

    static int getTileSizeForDirection(const MoveDirection& direction, const sf::Vector2u& mapTileSize);
    static int getChangingPosition(const MoveDirection& direction, const sf::Vector2f& position);

    MoveDirection currentlyFacingDirection;
    MoveDirection previousDirection;
    float moveSpeed;
};


#endif //NEWNEW_MOVABLEENTITY_H