#ifndef NEWNEW_NPCENTITY_H
#define NEWNEW_NPCENTITY_H


#include "../character/EntityAnimation.h"
#include "../character/EntityCollidable.h"
#include "../character/EntityState.h"
#include "../character/EntityMovement.h"
#include "EntityAutonomousMovement.h"

class NpcEntity : public sf::Sprite {

public:
    void initialize(sf::Texture* texture, const Collidable& collidable, sf::IntRect moveBoundaries);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void onPlayerInteractionStart(MoveDirection playerFacingDirection);
    void onPlayerInteractionFinish();
    void onCollisionEvent(const Collidable& collidedWith);
    EntityCollidable getEntityCollidable();
private:
    EntityState state;
    EntityAnimation entityAnimation;
    EntityCollidable entityCollidable;
    EntityAutonomousMovement entityAutonomousMovement;

    void initializeAnimations();
    void handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void handleInteractingState();
    void roundPosition();
};


#endif //NEWNEW_NPCENTITY_H
