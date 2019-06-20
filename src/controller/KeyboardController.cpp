#include "../../includes/controller/KeyboardController.h"

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
        case sf::Keyboard::Enter:
            printf("enter pressed\n");
            break;
        case sf::Keyboard::Space:
            //TODO: do I want to limit how many times/how often the player can hit this key? Otherwise we will spam playerManager with events
            printf("space pressed\n");
            eventBus->publish(new ControllerActionEvent());
        default:
            break;
    }
}

void KeyboardController::handleKeyReleasedEvent(sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Enter:
            printf("enter released\n");
            break;
        case sf::Keyboard::Space:
            printf("space released\n");
        default:
            break;
    }
}