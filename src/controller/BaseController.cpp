#include "../../includes/controller/BaseController.h"

void BaseController::initialize(std::shared_ptr<EventBus> eventBus) {
    this->eventBus = eventBus;
}

void BaseController::handleSfEvents(std::vector<sf::Event> sfEvents) {
    for(sf::Event event : sfEvents) {
        switch(event.type) {
            case sf::Event::KeyPressed:
                handleKeyPressedEvent(event.key.code);
                break;
            case sf::Event::KeyReleased:
                handleKeyReleasedEvent(event.key.code);
                break;
            default:
                break;
        }
    }
}