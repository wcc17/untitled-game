#ifndef NEWNEW_NPCENTITY_H
#define NEWNEW_NPCENTITY_H


#include "CharacterEntity.h"

class NpcEntity : public CharacterEntity {

public:
    void initialize(sf::Texture* texture, const Collidable& collidable, sf::IntRect moveBoundaries);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) override;
    void turnToFacePlayer(MoveDirection playerFacingDirection);
private:
    sf::IntRect moveBoundaries;
    sf::Time moveDelay;
    int distanceMoved = 0;
    int movementGoal = 0;

    void initializeAnimations() override;
    void handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) override;
    void handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) override;
    void handleInteractingState() override;

    bool moveDelayTimerDone(sf::Time deltaTime);
    void setupEntityMovement(const sf::Vector2u& mapTileSize);
    int getMaxDistanceEntityCanTravel(MoveDirection moveDirection);
    int determineRandomDistanceToMoveEntity(int maxDistanceEntityCanTravel, int tileSize);
    int getTileSizeForDirection(MoveDirection moveDirection, const sf::Vector2u& mapTileSize);
    bool flipCoin();
    void moveEntityTowardMovementGoal(sf::Vector2f previousPosition);
};


#endif //NEWNEW_NPCENTITY_H
