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

void PlayerManager::update(sf::Time deltaTime, sf::Vector2u mapTileSize) {
    //TODO: should the move function be moved into Player now? for now, player.update() has to be called after adjustPlayerAndViewPositions and thats dumb.
    player.move(deltaTime, currentDirection, mapTileSize);
    adjustPlayerAndViewPositions();
    player.update(deltaTime);
    currentDirection = MoveDirection::NONE;
}

void PlayerManager::draw(sf::RenderWindow* window) {
    window->draw(player);
}

void PlayerManager::onMoveEvent(ControllerMoveEvent* event) {
    currentDirection = event->direction;
}

//TODO: need to change how Collidable is inherited before the below stuff can change
//TODO: revisit this. Is there any point in a PlayerCollisionEvent having the player bounding box? We already know its the player
//TODO: need to refactor how getGlobalBounds and boundingBox work together. Having two variables do the same thing is dumb
void PlayerManager::onCollisionEvent(PlayerCollisionEvent* event) {
    Collidable playerCollidable = event->getCollision().first;
    Collidable otherCollidable = event->getCollision().second;

    player.getFixedPositionAfterCollision(playerCollidable.getBoundingBox(), otherCollidable.getBoundingBox(), player.getCurrentDirection());
    adjustPlayerAndViewPositions();
}

void PlayerManager::adjustPlayerAndViewPositions() {
    setViewCenterFromPlayerPosition();
    view.setCenter(std::round(view.getCenter().x), std::round(view.getCenter().y));

    //TODO: should this be done in MovableEntity so NPCs can also share this rounding functionality?
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

