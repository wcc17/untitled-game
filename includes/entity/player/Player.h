#ifndef NEWNEW_PLAYER_H
#define NEWNEW_PLAYER_H


#include "../character/AnimatedEntity.h"
#include "../../events/EventBus.h"
#include "../../controller/ControllerMoveEvent.h"
#include "../character/MovableEntity.h"
#include "../character/CollidableEntity.h"

class Player : public AnimatedEntity, public MovableEntity, public CollidableEntity {

public:
    void initialize(sf::Texture* texture, const Collidable& collidable);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void fixPositionAfterCollision(const Collidable& collidedWith);
    void roundPosition();
protected:
    void initializeAnimations();
};


#endif //NEWNEW_PLAYER_H
