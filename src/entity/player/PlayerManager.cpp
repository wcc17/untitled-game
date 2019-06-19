#include "../../../includes/entity/player/PlayerManager.h"

const float VIEW_SIZE_X = 320.f;
const float VIEW_SIZE_Y = 180.f;

void PlayerManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* playerTexture, const Collidable& playerCollidable) {
    this->eventBus = eventBus;

    player.initialize(playerTexture, playerCollidable);
    view.setSize(sf::Vector2f(VIEW_SIZE_X, VIEW_SIZE_Y));
    adjustPlayerAndViewPositions();

    eventBus->subscribe(this, &PlayerManager::onMoveEvent);
    eventBus->subscribe(this, &PlayerManager::onCollisionEvent);
}

void PlayerManager::update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    //TODO: the move function should be moved into Player now? for now, player.update() has to be called after adjustPlayerAndViewPositions and thats dumb.
    //TODO: to fix, player should keep a copy of its unrounded position so that it can be used to update the view position
    player.move(deltaTime, mapTileSize);
    adjustPlayerAndViewPositions();
    player.update(deltaTime);
}

void PlayerManager::draw(sf::RenderWindow* window) {
    window->draw(player);
}

void PlayerManager::onMoveEvent(ControllerMoveEvent* event) {
    player.setCurrentDirection(event->direction);
}

void PlayerManager::onCollisionEvent(PlayerCollisionEvent* event) {
    player.fixPositionAfterCollision(event->collidedWith);
    adjustPlayerAndViewPositions();
}

void PlayerManager::adjustPlayerAndViewPositions() {
    setViewCenterFromPlayerPosition();
    view.setCenter(std::round(view.getCenter().x), std::round(view.getCenter().y));

    //TODO: should this be done in MovableEntity so NPCs can also share this rounding functionality? should MovableEntity override setPosition?
    player.setPosition(std::round(player.getPosition().x), std::round(player.getPosition().y));
}

void PlayerManager::setViewCenterFromPlayerPosition() {
    view.setCenter(player.getPosition().x + (player.getGlobalBounds().width / 2), player.getPosition().y + (player.getGlobalBounds().height / 2));
}

Player PlayerManager::getPlayer() {
    return this->player;
}

sf::View PlayerManager::getView() {
    return this->view;
}

