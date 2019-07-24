#include "../../includes/controller/KeyboardController.h"

Logger KeyboardController::logger("KeyboardController");

void KeyboardController::initialize(std::shared_ptr<EventBus> eventBus) {
    BaseController::initialize(eventBus);
}

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
        //TODO: do I want to limit how many times/how often the player can hit these keys? Otherwise we will spam playerManager with events
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
        default:
            break;
    }
}