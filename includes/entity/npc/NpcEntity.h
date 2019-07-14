#ifndef NEWNEW_NPCENTITY_H
#define NEWNEW_NPCENTITY_H


#include "../character/EntityAnimation.h"
#include "../character/EntityCollidable.h"
#include "../character/EntityState.h"
#include "../character/EntityMovement.h"
#include "EntityAutonomousMovement.h"

class NpcEntity : public sf::Sprite {

public:
    void initialize(sf::Texture* texture, const Collidable& collidable, sf::IntRect moveBoundaries, std::string assetName);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void onPlayerInteractionStart(MoveDirection playerFacingDirection);
    void onPlayerInteractionFinish();
    void onCollisionEvent(const Collidable& collidedWith);
    EntityCollidable getEntityCollidable();
    std::string getAssetName();
private:
    EntityState state;
    EntityState stateBeforeInteraction;
    EntityAnimation entityAnimation;
    EntityCollidable entityCollidable;
    EntityAutonomousMovement entityAutonomousMovement;
    EntityLogger entityLogger;
    std::string assetName;

    float entityWidth;
    float entityHeight;

    void initializeAnimations();
    void handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void handleInteractingState(sf::Time deltaTime);
    void roundPosition();
    void setEntityPosition(const sf::Vector2f& position);
};


#endif //NEWNEW_NPCENTITY_H
