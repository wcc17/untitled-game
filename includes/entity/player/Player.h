#ifndef NEWNEW_PLAYER_H
#define NEWNEW_PLAYER_H


#include "../character/AnimatedEntity.h"
#include "../../events/EventBus.h"
#include "../../controller/ControllerMoveEvent.h"

class Player : public AnimatedEntity {

public:
    static const std::string COLLIDABLE_NAME;
    void initialize(sf::Texture* texture, std::string collidableName, CollidableType type, sf::FloatRect initialBoundingBox);
    void onControllerMoveEvent(MoveDirection direction);
    void update(sf::Time deltaTime);
    void setPlayerPositionFromViewCenter(sf::Vector2f viewCenter);
protected:
    void initializeAnimations();
};


#endif //NEWNEW_PLAYER_H
