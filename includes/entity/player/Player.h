#ifndef NEWNEW_PLAYER_H
#define NEWNEW_PLAYER_H


#include "../../events/EventBus.h"
#include "../../controller/ControllerMoveEvent.h"
#include "../character/CharacterEntity.h"

class Player : public CharacterEntity {

public:
    void initialize(sf::Texture* texture, const Collidable& collidable);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void fixPositionAfterCollision(const Collidable& collidedWith);
    void handleActionButtonPressed();
    void setActionButtonPressed();
protected:
    void initializeAnimations() override;
private:
    void resetAfterFrame();
    bool actionButtonPressed = false;
};


#endif //NEWNEW_PLAYER_H
