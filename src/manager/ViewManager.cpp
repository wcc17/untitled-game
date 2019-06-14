#include "../../includes/manager/ViewManager.h"

const float MOVEMENT_SPEED = 80.f;
const float VIEW_SIZE_X = 320.f;
const float VIEW_SIZE_Y = 180.f;

void ViewManager::initialize(std::shared_ptr<EventBus> eventBus) {
    this->eventBus = eventBus;
    eventBus->subscribe(this, &ViewManager::onMoveEvent);
}

void ViewManager::initializeViewForLevel(sf::Vector2f mapSizeInPixels) {
    view.setCenter(sf::Vector2f(mapSizeInPixels.x / 2, mapSizeInPixels.y / 2));
    view.setSize(sf::Vector2f(VIEW_SIZE_X, VIEW_SIZE_Y));
}

void ViewManager::update(sf::Time deltaTime) {
    moveView(deltaTime);
}

void ViewManager::onMoveEvent(MoveEvent* event) {
    resetMovement();
    switch(event->direction) {
        case MoveDirection::UP:
            movement.y -= MOVEMENT_SPEED;
            break;
        case MoveDirection::LEFT:
            movement.x -= MOVEMENT_SPEED;
            break;
        case MoveDirection::DOWN:
            movement.y += MOVEMENT_SPEED;
            break;
        case MoveDirection::RIGHT:
            movement.x += MOVEMENT_SPEED;
            break;
        case MoveDirection::NONE:
//            movement.x += MOVEMENT_SPEED;
            break;
        default:
            break;
    }
}

void ViewManager::moveView(sf::Time deltaTime) {
    previousPosition = view.getCenter();
    view.move(movement * deltaTime.asSeconds());
    roundViewCenter();
}

void ViewManager::resetMovement() {
    movement.x = 0;
    movement.y = 0;
}

void ViewManager::undoMovement() {
    view.setCenter(previousPosition);
}

sf::View ViewManager::getView() const {
    return this->view;
}

sf::Vector2f ViewManager::getViewPosition() {
    return this->view.getCenter();
}

void ViewManager::roundViewCenter() {
    //NOTE: rounding the position gets rid of weird artifacting/flickering that was introduced after tile maps. any negative repercussions?
    //NOTE: setting the position AFTER checking collisions, or else that will mess with the float precision collision detecting (i think)
    view.setCenter(std::round(view.getCenter().x), std::round(view.getCenter().y));
}