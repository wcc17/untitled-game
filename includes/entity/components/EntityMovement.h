#ifndef NEWNEW_ENTITYMOVEMENT_H
#define NEWNEW_ENTITYMOVEMENT_H


#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../controller/MoveDirection.h"
#include "EntityState.h"
#include "../../util/Logger.h"
#include "EntityLogger.h"

class EntityMovement {
public:
    void initialize(std::string entityName, float moveSpeed);
    void handleStanding(sf::Time deltaTime, EntityState& state, MoveDirection& currentDirection, sf::Vector2f& currentPosition);
    void handleMoving(sf::Time deltaTime, const sf::Vector2u& mapTileSize, EntityState& state, MoveDirection& currentDirection, sf::Vector2f& currentPosition);
    MoveDirection getLastFacingDirection() const;
    void performRegularMoveOnCurrentPosition(sf::Time deltaTime, MoveDirection& currentDirection, sf::Vector2f& currentPosition);
    void performGoalLimitedMoveOnCurrentPosition(sf::Time deltaTime, const sf::Vector2u& mapTileSize, MoveDirection& currentDirection, sf::Vector2f& currentPosition);

private:
    sf::Vector2f getRegularMovement(float speed, MoveDirection& currentDirection);
    sf::Vector2f getGoalLimitedMovement(sf::Time deltaTime, const sf::Vector2u& mapTileSize, MoveDirection& currentDirection, sf::Vector2f currentPosition);
    bool movementGoalReached(const sf::Vector2u& mapTileSize, sf::Vector2f currentPosition);
    void performMoveOnCurrentPosition(sf::Time deltaTime, sf::Vector2f moveVector, sf::Vector2f& currentPosition);
    int getTileSizeForDirection(const MoveDirection& direction, const sf::Vector2u& mapTileSize);
    int getChangingPosition(const MoveDirection& direction, const sf::Vector2f& position);

    MoveDirection lastFacingDirection; //NOTE: only used to get the last direction the player was facing. Should not be assigned anywhere else except when direction initially changes. Since previousDirection is used elsewhere, not using it
    MoveDirection previousDirection;
    float moveSpeed;

    EntityLogger entityLogger;
};


#endif //NEWNEW_ENTITYMOVEMENT_H
