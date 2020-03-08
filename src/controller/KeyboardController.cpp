#include "../../includes/controller/KeyboardController.h"

Logger KeyboardController::logger("KeyboardController");

void KeyboardController::initialize(std::shared_ptr<EventBus> eventBus) {
    BaseController::initialize(eventBus);
}

/**
 * handleInput(..)
 * handleSfEvents makes a call to either handleKeyPressedEvent or handleKeyReleasedEvent
 * movement keys are handled seperately.
 *
 * sf::Keyboard::isKeyPressed is used for movement, as it only cares whether a key was pressed or not
 * sf::Event::KeyPressed (checked in handleSfEvents) is used to trigger something the moment a key is pressed
**/

void KeyboardController::handleInput(std::vector<sf::Event> sfEvents) {
    BaseController::handleSfEvents(sfEvents);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        eventBus->publish(new ControllerMoveEvent(MoveDirection::UP));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        eventBus->publish(new ControllerMoveEvent(MoveDirection::LEFT));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        eventBus->publish(new ControllerMoveEvent(MoveDirection::DOWN));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        eventBus->publish(new ControllerMoveEvent(MoveDirection::RIGHT));
    } else {
        //TODO: should this be called every frame? Its really not that different from anything else. The method tied to the event still only gets called once every frame
        eventBus->publish(new ControllerMoveEvent(MoveDirection::NONE));
    }
}

void KeyboardController::handleKeyPressedEvent(sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Enter:
            logger.logDebug("enter pressed");
            eventBus->publish(new ControllerMenuEvent());
            break;
        case sf::Keyboard::Space:
            logger.logDebug("space pressed");
            eventBus->publish(new ControllerActionEvent());
            break;
        case sf::Keyboard::Escape:
            logger.logDebug("escape pressed");
            eventBus->publish(new ControllerCancelEvent());
            break;
        case sf::Keyboard::W:
            logger.logDebug("w pressed");
            eventBus->publish(new ControllerMenuMoveEvent(MoveDirection::UP));
            break;
        case sf::Keyboard::S:
            logger.logDebug("s pressed");
            eventBus->publish(new ControllerMenuMoveEvent(MoveDirection::DOWN));
            break;
        case sf::Keyboard::F1:
            eventBus->printSubscriptionsToConsole();
            break;
        default:
            break;
    }
}

void KeyboardController::handleKeyReleasedEvent(sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Enter:
            logger.logDebug("enter released");
            break;
        case sf::Keyboard::Space:
            logger.logDebug("space released");
            break;
        default:
            break;
    }
}