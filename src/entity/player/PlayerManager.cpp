#include "../../../includes/entity/player/PlayerManager.h"

const float VIEW_SIZE_X = 320.f;
const float VIEW_SIZE_Y = 180.f;

void PlayerManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* playerTexture, Collidable playerCollidable) {
    this->eventBus = eventBus;

    player.initialize(playerTexture, playerCollidable.getName(), playerCollidable.getType(), playerCollidable.getBoundingBox());
    view.setSize(sf::Vector2f(VIEW_SIZE_X, VIEW_SIZE_Y));
    adjustPlayerAndViewPositions();

    eventBus->subscribe(this, &PlayerManager::onMoveEvent);
    eventBus->subscribe(this, &PlayerManager::onCollisionEvent);
}

void PlayerManager::update(sf::Time deltaTime) {
    move(deltaTime);
    player.update(deltaTime);
}

void PlayerManager::draw(sf::RenderWindow* window) {
    window->draw(player);
}

void PlayerManager::move(sf::Time deltaTime) {
    player.move(deltaTime);
    adjustPlayerAndViewPositions();
}

//called only when a button is pressed, does not actually move the player
void PlayerManager::onMoveEvent(ControllerMoveEvent* event) {
    player.onControllerMoveEvent(event->direction);
}

void PlayerManager::onCollisionEvent(PlayerCollisionEvent* event) {
    Collidable playerCollidable = event->getCollision().first;
    Collidable otherCollidable = event->getCollision().second;

    sf::Vector2f newPosition = player.getFixedPositionAfterCollision(playerCollidable.getBoundingBox(), otherCollidable.getBoundingBox(), player.getMovement());
    player.setPosition(newPosition);
    adjustPlayerAndViewPositions();
}

void PlayerManager::adjustPlayerAndViewPositions() {
    //NOTE: rounding the position gets rid of weird artifacting/flickering that was introduced after tile maps. any negative repercussions yet?
    setViewCenterFromPlayerPosition(); //first set the view center
    view.setCenter(std::round(view.getCenter().x), std::round(view.getCenter().y)); //round the view
    player.setPosition(std::round(player.getPosition().x), std::round(player.getPosition().y));
}

void PlayerManager::setViewCenterFromPlayerPosition() {
    view.setCenter(player.getPosition().x + (player.getGlobalBounds().width / 2), player.getPosition().y + (player.getGlobalBounds().height / 2));
}

Player PlayerManager::getPlayer() const {
    return this->player;
}

sf::View PlayerManager::getView() const {
    return this->view;
}

