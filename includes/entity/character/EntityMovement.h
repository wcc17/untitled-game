#ifndef NEWNEW_ENTITYMOVEMENT_H
#define NEWNEW_ENTITYMOVEMENT_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../controller/MoveDirection.h"
#include "../character/EntityState.h"

class EntityMovement {
public:
    void initialize(float moveSpeed);
    void handleStandingState(sf::Time deltaTime, EntityState& state, MoveDirection& currentDirection, sf::Vector2f& currentPosition);
    void handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize, EntityState& state, MoveDirection& currentDirection, sf::Vector2f& currentPosition);
    MoveDirection getLastFacingDirection();
    sf::Vector2f getRegularMovement(float speed, MoveDirection& currentDirection);
    sf::Vector2f getGoalLimitedMovement(sf::Time deltaTime, const sf::Vector2u& mapTileSize, MoveDirection& currentDirection, sf::Vector2f currentPosition);

private:
    bool movementGoalReached(const sf::Vector2u& mapTileSize, sf::Vector2f currentPosition);
    void performRegularMove(sf::Time deltaTime, MoveDirection& currentDirection, sf::Vector2f& currentPosition);
    void performGoalLimitedMove(sf::Time deltaTime, const sf::Vector2u& mapTileSize, MoveDirection& currentDirection, sf::Vector2f& currentPosition);

    static int getTileSizeForDirection(const MoveDirection& direction, const sf::Vector2u& mapTileSize);
    static int getChangingPosition(const MoveDirection& direction, const sf::Vector2f& position);

    MoveDirection lastFacingDirection; //NOTE: only used to get the last direction the player was facing. Should not be assigned anywhere else except when direction initially changes. Since previousDirection is used elsewhere, not using it
    MoveDirection previousDirection;
    float moveSpeed;
};


#endif //NEWNEW_ENTITYMOVEMENT_H
