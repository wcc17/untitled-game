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
    void update(sf::Time deltaTime);
    void move(sf::Time deltaTime, const MoveDirection& direction, const sf::Vector2u& mapTileSize);
protected:
    void initializeAnimations();
};


#endif //NEWNEW_PLAYER_H
