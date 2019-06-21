#include "../../../includes/entity/player/PlayerManager.h"

const float VIEW_SIZE_X = 320.f;
const float VIEW_SIZE_Y = 180.f;

void PlayerManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* playerTexture, const Collidable& playerCollidable) {
    this->eventBus = eventBus;
    this->view = std::make_unique<sf::View>();

    player.initialize(eventBus, playerTexture, playerCollidable);
    view->setSize(sf::Vector2f(VIEW_SIZE_X, VIEW_SIZE_Y));
    adjustPlayerAndViewPositions();

    eventBus->subscribe(this, &PlayerManager::onCollisionEvent);
}

void PlayerManager::update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    player.update(deltaTime, mapTileSize);
    adjustPlayerAndViewPositions();
}

void PlayerManager::draw(sf::RenderWindow* window) {
    window->draw(player);
}

void PlayerManager::onCollisionEvent(PlayerCollisionEvent* event) {
    //TODO: this is the only event being handled in PlayerManager. Could move view out of this class again and send an event to its manager when the player updates its position if I wanted to re-seperate player and view
    player.fixPositionAfterCollision(event->collidedWith);
    adjustPlayerAndViewPositions();
}

void PlayerManager::adjustPlayerAndViewPositions() {
    setViewCenterFromPlayerPosition();
    view->setCenter(std::round(view->getCenter().x), std::round(view->getCenter().y));
    player.roundPosition();
}

void PlayerManager::setViewCenterFromPlayerPosition() {
    view->setCenter(player.getPosition().x + (player.getGlobalBounds().width / 2), player.getPosition().y + (player.getGlobalBounds().height / 2));
}

Player PlayerManager::getPlayer() {
    return this->player;
}

sf::View* PlayerManager::getView() {
    return this->view.get();
}
