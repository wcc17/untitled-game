#ifndef NEWNEW_PLAYER_H
#define NEWNEW_PLAYER_H


#include "../../events/EventBus.h"
#include "../../controller/ControllerMoveEvent.h"
#include "../character/CharacterEntity.h"
#include "../../collisions/PlayerVicinityCollisionEvent.h"
#include "../../text/CloseDialogueEvent.h"
#include "../../controller/ControllerActionEvent.h"
#include "../../../includes/text/OpenDialogueEvent.h"
#include "../../collisions/PlayerCollisionEvent.h"
#include "PlayerPositionChangeEvent.h"

class Player : public CharacterEntity {

public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, const Collidable& collidable);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
protected:
    void initializeAnimations() override;
private:
    std::shared_ptr<EventBus> eventBus;
    bool actionButtonPressed = false;

    void handleStandingState(sf::Time deltaTime);
    void handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void handleInteractingState();
    void resetAfterFrame();

    void handleActionButtonPressed();
    void adjustPlayerAndViewPositions();

    void onControllerMoveEvent(ControllerMoveEvent* event);
    void onControllerActionEvent(ControllerActionEvent* event);
    void onVicinityCollisionEvent(PlayerVicinityCollisionEvent* event);
    void onCloseDialogueEvent(CloseDialogueEvent* event);
    void onCollisionEvent(PlayerCollisionEvent* event);
};


#endif //NEWNEW_PLAYER_H
