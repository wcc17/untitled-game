#ifndef NEWNEW_PLAYER_H
#define NEWNEW_PLAYER_H


#include "AnimatedEntity.h"
#include "../../events/EventBus.h"
#include "../../controller/ControllerMoveEvent.h"
#include "../../../includes/view/PlayerMoveEvent.h"

class Player : public AnimatedEntity {

public:
    static const std::string COLLIDABLE_NAME;
    void initialize(sf::Texture* texture, float windowWidth, float windowHeight, std::shared_ptr<EventBus> eventBus);
    void update(sf::Time deltaTime);
protected:
    std::shared_ptr<EventBus> eventBus;
    void initializeAnimations();
    void updatePlayerPosition(sf::Vector2f viewCenter);
    void onControllerMoveEvent(ControllerMoveEvent* event);
    void onPlayerMoveEvent(PlayerMoveEvent* event);
};


#endif //NEWNEW_PLAYER_H
