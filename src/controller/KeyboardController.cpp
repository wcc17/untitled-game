#include "../../includes/controller/KeyboardController.h"
#include "../../includes/controller/ControllerMoveEvent.h"

void KeyboardController::initialize(std::shared_ptr<EventBus> eventBus) {
    BaseController::initialize(eventBus);
}

void KeyboardController::handleInput(std::vector<sf::Event> sfEvents) {
    BaseController::handleSfEvents(sfEvents);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        eventBus->publish(new ControllerMoveEvent(MoveDirection::UP));
        shouldSendStopMovementEvent = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        eventBus->publish(new ControllerMoveEvent(MoveDirection::LEFT));
        shouldSendStopMovementEvent = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        eventBus->publish(new ControllerMoveEvent(MoveDirection::DOWN));
        shouldSendStopMovementEvent = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        eventBus->publish(new ControllerMoveEvent(MoveDirection::RIGHT));
        shouldSendStopMovementEvent = true;
    } else {
        if(shouldSendStopMovementEvent) {
            eventBus->publish(new ControllerMoveEvent(MoveDirection::NONE));
            shouldSendStopMovementEvent = false;
        }

    }
}

void KeyboardController::handleKeyPressedEvent(sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Enter:
            printf("enter pressed\n");
            break;
        default:
            break;
    }
}

void KeyboardController::handleKeyReleasedEvent(sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Enter:
            printf("enter released\n");
            break;
        default:
            break;
    }
}