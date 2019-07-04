#ifndef NEWNEW_ENTITYAUTONOMOUSMOVEMENT_H
#define NEWNEW_ENTITYAUTONOMOUSMOVEMENT_H


#include <random>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include "../../controller/MoveDirection.h"
#include "../character/EntityMovement.h"

class EntityAutonomousMovement {
public:
    void initialize(sf::IntRect moveBoundaries, float moveSpeed);
    void handleStanding(sf::Time deltaTime, const sf::Vector2u& mapTileSize, EntityState& state, sf::Vector2f& currentPosition);
    void handleMoving(sf::Time deltaTime, const sf::Vector2u& mapTileSize, sf::Vector2f& currentPosition, EntityState& state);
    void resetDistanceMoved();
    MoveDirection getCurrentDirection();
    void setCurrentDirection(MoveDirection direction);
private:
    EntityMovement entityMovement;
    std::random_device randomDevice; // obtain a random number from hardware
    sf::IntRect moveBoundaries;
    sf::Time moveDelay;
    int distanceMoved = 0;
    int movementGoal = 0;
    float moveSpeed = 0;
    MoveDirection currentDirection;

    void setMoveDelayTimer();
    bool moveDelayTimerDone(sf::Time deltaTime);

    void setupEntityMovement(const sf::Vector2u& mapTileSize, EntityState& state, sf::Vector2f& currentPosition);
    int getMaxDistanceEntityCanTravel(MoveDirection moveDirection, sf::Vector2f currentPosition);
    void ensureEntityInsideBounds(sf::Vector2f& currentPosition);
    void ensureEntityPositionAlignedWithTileSize(const sf::Vector2u& mapTileSize, sf::Vector2f& currentPosition);

    MoveDirection chooseRandomDirection();
    int determineRandomDistanceToMoveEntity(int maxDistanceEntityCanTravel, int tileSize);
    int getRandomIntInRange(int min, int max);
    float getRandomFloatInRange(float min, float max);
    bool decideIfNpcShouldMove();
    static int getTileSizeForDirection(MoveDirection moveDirection, const sf::Vector2u& mapTileSize);

};


#endif //NEWNEW_ENTITYAUTONOMOUSMOVEMENT_H
