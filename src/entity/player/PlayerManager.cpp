#include "../../../includes/entity/player/PlayerManager.h"

const float MOVEMENT_SPEED = 80.f;
const float VIEW_SIZE_X = 320.f;
const float VIEW_SIZE_Y = 180.f;

void PlayerManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* playerTexture, Collidable playerCollidable) {
    this->eventBus = eventBus;

    player.initialize(playerTexture, playerCollidable.getName(), playerCollidable.getType(), playerCollidable.getBoundingBox());
    setViewCenterFromPlayerPosition();
    view.setSize(sf::Vector2f(VIEW_SIZE_X, VIEW_SIZE_Y));

    eventBus->subscribe(this, &PlayerManager::onMoveEvent);
    eventBus->subscribe(this, &PlayerManager::onCollisionEvent);
}

void PlayerManager::update(sf::Time deltaTime) {
    moveView(deltaTime);
    player.update(deltaTime);
}

void PlayerManager::draw(sf::RenderWindow* window) {
    window->draw(player);
}

void PlayerManager::moveView(sf::Time deltaTime) {
    moveView(movement * deltaTime.asSeconds());
}

void PlayerManager::moveView(sf::Vector2f movementVector) {
    view.move(movementVector);
    roundViewCenter();
    player.setPlayerPositionFromViewCenter(view.getCenter());
}

void PlayerManager::setViewCenterFromPlayerPosition() {
    float centerX = (player.getBoundingBox().width / 2) + player.getBoundingBox().left;
    float centerY = (player.getBoundingBox().height / 2) + player.getBoundingBox().top;
    view.setCenter(centerX, centerY);
//    roundViewCenter();

    if(centerX != view.getCenter().x || centerY != view.getCenter().y) {
        printf("player position needs to be adjusted after rounding the view manager center position upon initialization\n");
    }
}

void PlayerManager::onMoveEvent(ControllerMoveEvent* event) {
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

    player.onControllerMoveEvent(event->direction);
}

void PlayerManager::onCollisionEvent(PlayerCollisionEvent* event) {
    Collidable playerCollidable = event->getCollision().first;
    Collidable otherCollidable = event->getCollision().second;
    fixPositionOnCollision(playerCollidable.getBoundingBox(), otherCollidable.getBoundingBox());
}

void PlayerManager::fixPositionOnCollision(sf::FloatRect playerRect, sf::FloatRect otherRect) {
    bool isColliding = true;
    float left = playerRect.left;
    float top = playerRect.top;
    while(isColliding) {
        if(movement.x == 0.f && movement.y == 0.f) {
            //TODO: reset the players position at the start of the level.
            printf("error with player collision - the player didn't move into this collision so theres no way to move him out\n");
        }

        if(movement.x > 0.f) {
            moveView({-1, 0});
            left -= 1;
        } else if(movement.x < 0.f) {
            moveView({1, 0});
            left += 1;
        }

        if(movement.y > 0.f) {
            moveView({0, -1});
            top -= 1;
        } else if(movement.y < 0.f) {
            moveView({0, 1});
            top += 1;
        }

        sf::FloatRect newBounds = sf::FloatRect(left, top, playerRect.width, playerRect.height);
        if(!newBounds.intersects(otherRect)) {
            isColliding = false;
        }
    }
}

void PlayerManager::roundViewCenter() {
    //NOTE: rounding the position gets rid of weird artifacting/flickering that was introduced after tile maps. any negative repercussions?
    //NOTE: setting the position AFTER checking collisions, or else that will mess with the float precision collision detecting (i think)
    view.setCenter(std::round(view.getCenter().x), std::round(view.getCenter().y));
}

void PlayerManager::resetMovement() {
    movement.x = 0;
    movement.y = 0;
}

Player PlayerManager::getPlayer() const {
    return this->player;
}

sf::View PlayerManager::getView() const {
    return this->view;
}

