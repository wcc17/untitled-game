#ifndef NEWNEW_NPCENTITY_H
#define NEWNEW_NPCENTITY_H


#include <random>
#include "AnimatedEntity.h"
#include "MovableEntity.h"
#include "CollidableEntity.h"

class NpcEntity : public AnimatedEntity, public MovableEntity, public CollidableEntity {

public:
    void initialize(sf::Texture* texture, const Collidable& collidable, sf::IntRect moveBoundaries);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void onPlayerInteractionStart(MoveDirection playerFacingDirection);
    void onPlayerInteractionFinish();
    void onCollisionEvent(const Collidable& collidedWith);
private:
    EntityState state;
    sf::IntRect moveBoundaries;
    sf::Time moveDelay;
    int distanceMoved = 0;
    int movementGoal = 0;
    std::random_device randomDevice; // obtain a random number from hardware

    void initializeAnimations() override;
    void handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void handleInteractingState();
    void roundPosition();

    void setMoveDelayTimer();
    bool moveDelayTimerDone(sf::Time deltaTime);

    void setupEntityMovement(const sf::Vector2u& mapTileSize);
    int getMaxDistanceEntityCanTravel(MoveDirection moveDirection);
    void handleEntityMovementTowardGoal(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void ensureEntityInsideBounds();
    void ensureEntityPositionAlignedWithTileSize(const sf::Vector2u& mapTileSize);

    MoveDirection chooseRandomDirection();
    int determineRandomDistanceToMoveEntity(int maxDistanceEntityCanTravel, int tileSize);
    int getRandomIntInRange(int min, int max);
    float getRandomFloatInRange(float min, float max);
    bool decideIfNpcShouldMove();
    static int getTileSizeForDirection(MoveDirection moveDirection, const sf::Vector2u& mapTileSize);
};


#endif //NEWNEW_NPCENTITY_H
