#ifndef NEWNEW_CHARACTERENTITY_H
#define NEWNEW_CHARACTERENTITY_H


#include "MovableEntity.h"
#include "CollidableEntity.h"
#include "AnimatedEntity.h"

class CharacterEntity : public AnimatedEntity, public MovableEntity, public CollidableEntity {
public:
    void initialize(sf::Texture* texture, float movementSpeed, const Collidable& collidable, float FrameTime);
    virtual void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void roundPosition();
protected:
    EntityState state;
    virtual void handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    virtual void handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    virtual void handleInteractingState() {};
};


#endif //NEWNEW_CHARACTERENTITY_H
