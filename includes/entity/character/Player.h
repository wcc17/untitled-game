#ifndef NEWNEW_PLAYER_H
#define NEWNEW_PLAYER_H


#include "AnimatedEntity.h"
#include "../../events/EventBus.h"
#include "../../controller/MoveEvent.h"

class Player : public AnimatedEntity {

public:
    void initialize(sf::Texture* texture, float windowWidth, float windowHeight, std::shared_ptr<EventBus> eventBus);
    void update(sf::Time deltaTime, sf::Vector2f viewCenter);
    void updatePlayerPosition(sf::Vector2f viewCenter);
protected:
    std::shared_ptr<EventBus> eventBus;
    void initializeAnimations();
    void onMoveEvent(MoveEvent* event);
};


#endif //NEWNEW_PLAYER_H
