#include "../../includes/scene/ViewManager.h"

const float VIEW_SIZE_X = 320.f;
const float VIEW_SIZE_Y = 180.f;

void ViewManager::initialize(std::shared_ptr<EventBus> eventBus) {
    view.setSize(sf::Vector2f(VIEW_SIZE_X, VIEW_SIZE_Y));
    eventBus->subscribe(this, &ViewManager::onPlayerPositionChanged);
}

void ViewManager::onPlayerPositionChanged(PlayerPositionChangeEvent* event) {
    setViewCenterFromPlayerPosition(event->playerBounds);
    view.setCenter(std::round(view.getCenter().x), std::round(view.getCenter().y));
}

void ViewManager::setViewCenterFromPlayerPosition(sf::FloatRect playerBounds) {
    view.setCenter(playerBounds.left + (playerBounds.width / 2), playerBounds.top + (playerBounds.height / 2));
}

sf::View ViewManager::getView() {
    return this->view;
}
