#ifndef NEWNEW_PLAYER_H
#define NEWNEW_PLAYER_H


#include "../character/AnimatedEntity.h"
#include "../../events/EventBus.h"
#include "../../controller/ControllerMoveEvent.h"
#include "../character/MovableEntity.h"

class Player : public AnimatedEntity, public MovableEntity, public Collidable {

public:
    void initialize(sf::Texture* texture, std::string collidableName, CollidableType collidableType, sf::FloatRect initialBoundingBox);
    void update(sf::Time deltaTime);
    void move(sf::Time deltaTime, MoveDirection direction);
protected:
    void initializeAnimations();
};


#endif //NEWNEW_PLAYER_H
