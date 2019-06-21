#ifndef NEWNEW_PLAYER_H
#define NEWNEW_PLAYER_H


#include "../../events/EventBus.h"
#include "../../controller/ControllerMoveEvent.h"
#include "../character/CharacterEntity.h"
#include "../../collisions/PlayerVicinityCollisionEvent.h"
#include "../../controller/ControllerActionEvent.h"
#include "../../../includes/text/OpenDialogueEvent.h"
#include "../../text/CloseDialogueEvent.h"

class Player : public CharacterEntity {

public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, const Collidable& collidable);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void fixPositionAfterCollision(const Collidable& collidedWith);
    void handleActionButtonPressed();

    void onControllerMoveEvent(ControllerMoveEvent* event);
    void onControllerActionEvent(ControllerActionEvent* event);
    void onVicinityCollisionEvent(PlayerVicinityCollisionEvent* event);
    void onCloseDialogueEvent(CloseDialogueEvent* event);
protected:
    void initializeAnimations() override;
private:
    std::shared_ptr<EventBus> eventBus;
    void resetAfterFrame();
    bool actionButtonPressed = false;

    void handleStandingState(sf::Time deltaTime);
    void handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void handleInteractingState();
};


#endif //NEWNEW_PLAYER_H
