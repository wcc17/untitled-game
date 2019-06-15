#include <SFML/Graphics/PrimitiveType.hpp>
#include "../../includes/view/ViewManager.h"
#include "../../includes/entity/character/Player.h"

const float MOVEMENT_SPEED = 80.f;
const float VIEW_SIZE_X = 320.f;
const float VIEW_SIZE_Y = 180.f;

void ViewManager::initialize(std::shared_ptr<EventBus> eventBus) {
    this->eventBus = eventBus;
    eventBus->subscribe(this, &ViewManager::onMoveEvent);
    eventBus->subscribe(this, &ViewManager::onCollisionEvent);
}

void ViewManager::initializeViewForLevel(sf::Vector2f mapSizeInPixels) {
    view.setCenter(sf::Vector2f(mapSizeInPixels.x / 2, mapSizeInPixels.y / 2));
    view.setSize(sf::Vector2f(VIEW_SIZE_X, VIEW_SIZE_Y));
}

void ViewManager::update(sf::Time deltaTime) {
    moveView(deltaTime);
}

void ViewManager::onMoveEvent(ControllerMoveEvent* event) {
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
            break;
        default:
            break;
    }
}

void ViewManager::moveView(sf::Time deltaTime) {
    //TODO: players bottom left coordinate (left, top + height) should always match up to the 8x8 "tiles" designated on the tileset from Tiled
    view.move(movement * deltaTime.asSeconds());
    roundViewCenter();
    eventBus->publish(new PlayerMoveEvent(view.getCenter()));
}

void ViewManager::onCollisionEvent(PlayerCollisionEvent* event) {
    Collidable playerCollidable = event->getCollision().first;
    Collidable otherCollidable = event->getCollision().second;
    fixPositionOnCollision(playerCollidable.getBoundingBox(), otherCollidable.getBoundingBox());
}

void ViewManager::fixPositionOnCollision(sf::FloatRect playerRect, sf::FloatRect otherRect) {
    bool isColliding = true;
    float left = playerRect.left;
    float top = playerRect.top;
    while(isColliding) {
        if(movement.x > 0.f) {
            view.move(-1, 0);
            left -= 1;
        } else if(movement.x < 0.f) {
            view.move(1, 0);
            left += 1;
        }

        if(movement.y > 0.f) {
            view.move(0, -1);
            top -= 1;
        } else if(movement.y < 0.f) {
            view.move(0, 1);
            top += 1;
        }

        sf::FloatRect newBounds = sf::FloatRect(left, top, playerRect.width, playerRect.height);
        if(!newBounds.intersects(otherRect)) {
            isColliding = false;
        }
    }

    eventBus->publish(new PlayerMoveEvent(view.getCenter()));
}

void ViewManager::resetMovement() {
    movement.x = 0;
    movement.y = 0;
}

sf::View ViewManager::getView() const {
    return this->view;
}

void ViewManager::roundViewCenter() {
    //NOTE: rounding the position gets rid of weird artifacting/flickering that was introduced after tile maps. any negative repercussions?
    //NOTE: setting the position AFTER checking collisions, or else that will mess with the float precision collision detecting (i think)
    view.setCenter(std::round(view.getCenter().x), std::round(view.getCenter().y));
}