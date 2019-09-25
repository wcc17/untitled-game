#ifndef NEWNEW_NPCENTITY_H
#define NEWNEW_NPCENTITY_H


#include "../components/EntityAnimation.h"
#include "../components/EntityCollidable.h"
#include "../components/EntityState.h"
#include "../components/EntityMovement.h"
#include "../components/EntityAutonomousMovement.h"
#include "types/NpcType.h"

class NpcEntity : public sf::Sprite {

public:
    virtual void initialize(
            sf::Texture* texture, const Collidable& collidable,
            sf::IntRect moveBoundaries, std::string assetName,
            bool isAggressive, NpcType npcType);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void onPlayerInteractionStart(MoveDirection playerFacingDirection);
    void onPlayerInteractionFinish();
    void onCollisionEvent(const Collidable& collidedWith);
    EntityCollidable getEntityCollidable();
    std::string getAssetName();
    bool isMoving();
    bool isNpcAggressive();

protected:
    EntityAnimation entityAnimation;
    float entitySpeed;
    float entityFrameTime;
    float entityWidth;
    float entityHeight;
    sf::Vector2f moveDelayRange;
    virtual void initializeAnimations() {};

private:
    EntityState state;
    EntityState stateBeforeInteraction;
    EntityCollidable entityCollidable;
    EntityAutonomousMovement entityAutonomousMovement;
    EntityLogger entityLogger;
    std::string assetName;
    bool isAggressive = false;
    NpcType npcType;

    void handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void handleInteractingState(sf::Time deltaTime);
    void roundPosition();
    void setEntityPosition(const sf::Vector2f& position);
};


#endif //NEWNEW_NPCENTITY_H
