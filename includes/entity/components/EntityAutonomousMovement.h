#ifndef NEWNEW_ENTITYAUTONOMOUSMOVEMENT_H
#define NEWNEW_ENTITYAUTONOMOUSMOVEMENT_H


#include <random>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include "../../controller/MoveDirection.h"
#include "EntityMovement.h"
#include "../../util/Logger.h"
#include "EntityLogger.h"

class EntityAutonomousMovement {
public:
    void initialize(std::string npcName, sf::IntRect moveBoundaries, float moveSpeed, sf::Vector2f moveDelayRange);
    void handleStanding(sf::Time deltaTime, const sf::Vector2u& mapTileSize, EntityState& state, const sf::Vector2f& currentPosition);
    sf::Vector2f handleMoveAndReturnPosition(sf::Time deltaTime, sf::Vector2f currentPosition, EntityState& state);
    MoveDirection getCurrentDirection();
    void stopMovement(EntityState& state);
    sf::Vector2f fixInvalidPosition(const sf::Vector2f& currentPosition, const sf::Vector2u& mapTileSize);
private:
    sf::IntRect moveBoundaries;
    sf::Time moveDelay;
    sf::Vector2f moveDelayRange;
    float movementGoal = 0;
    float moveSpeed = 0;
    MoveDirection currentDirection;

    std::random_device randomDevice; // obtain a random number from hardware //TODO: should this be static?
    EntityLogger entityLogger;

    void setMoveDelayTimer();
    bool moveDelayTimerDone(sf::Time deltaTime);
    float fixInvalidCoordinate(float coord, float tileSize);
    void move(sf::Time deltaTime, sf::Vector2f& currentPosition);
    void checkMovementGoal(sf::Vector2f& currentPosition, EntityState& state);
    void setupEntityMovement(const sf::Vector2u& mapTileSize, EntityState& state, const sf::Vector2f& currentPosition);
    int getMaxDistanceEntityCanTravel(MoveDirection moveDirection, sf::Vector2f currentPosition);
    MoveDirection chooseRandomDirection();
    int determineRandomDistanceToMoveEntity(int maxDistanceEntityCanTravel, int tileSize);
    int getRandomIntInRange(int min, int max);
    float getRandomFloatInRange(float min, float max);
    bool decideIfNpcShouldMove();
    int getTileSizeForDirection(MoveDirection moveDirection, const sf::Vector2u& mapTileSize);
    sf::Vector2f getRegularMovement(float speed);
};


#endif //NEWNEW_ENTITYAUTONOMOUSMOVEMENT_H
