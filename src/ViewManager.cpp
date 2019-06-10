#include "../includes/ViewManager.h"

const float MOVEMENT_SPEED = 100.f;

void ViewManager::initializeViewForLevel(sf::Vector2f mapSizeInPixels, sf::Vector2u windowSize) {
    view.setCenter(sf::Vector2f(mapSizeInPixels.x / 2, mapSizeInPixels.y / 2));
    view.setSize(sf::Vector2f(windowSize.x / 5, windowSize.y / 5));
}

void ViewManager::update(sf::Time deltaTime) {
    //    printf("position: %f, %f \n", view.getCenter().x, view.getCenter().y);
    view.move(movement * deltaTime.asSeconds());

    //NOTE: rounding the position gets rid of weird artifacting/flickering that was introduced after tile maps. any negative repercussions?
    //NOTE: setting the position AFTER checking collisions, or else that will mess with the float precision collision detecting (i think)
    view.setCenter(std::round(view.getCenter().x), std::round(view.getCenter().y));
}

void ViewManager::moveUp() {
    resetMovement();
    movement.y -= MOVEMENT_SPEED;
}

void ViewManager::moveLeft() {
    resetMovement();
    movement.x -= MOVEMENT_SPEED;
}

void ViewManager::moveDown() {
    resetMovement();
    movement.y += MOVEMENT_SPEED;
}

void ViewManager::moveRight() {
    resetMovement();
    movement.x += MOVEMENT_SPEED;
}

void ViewManager::stop() {
    resetMovement();
}

void ViewManager::resetMovement() {
    movement.x = 0;
    movement.y = 0;
}

sf::View ViewManager::getView() const {
    return this->view;
}

sf::Vector2f ViewManager::getViewPosition() {
    return this->view.getCenter();
}
