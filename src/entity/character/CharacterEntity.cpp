#include "../../../includes/entity/character/CharacterEntity.h"

void CharacterEntity::initialize(sf::Texture* texture, float movementSpeed, const Collidable& collidable, float frameTime) {
    AnimatedEntity::initialize(texture);
    MovableEntity::initialize(movementSpeed);

    this->state = STATE_STANDING;
    this->name = collidable.getName();
    this->type = collidable.getType();
    this->setPosition(sf::Vector2f(collidable.getBoundingBox().left, collidable.getBoundingBox().top));

    setFrameTime(sf::seconds(frameTime));
    initializeAnimations();
}

void CharacterEntity::update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    switch(state) {
        case STATE_STANDING:
            handleStandingState(deltaTime);
            break;
        case STATE_MOVING:
            handleMovingState(deltaTime, mapTileSize);
            break;
        case STATE_INTERACTING:
            handleInteractingState();
            break;
    }
}

void CharacterEntity::handleStandingState(sf::Time deltaTime) {
    MovableEntity::handleStandingState(deltaTime, state);
    AnimatedEntity::update(deltaTime, currentDirection);
}

void CharacterEntity::handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    MovableEntity::handleMovingState(deltaTime, mapTileSize, state);
    AnimatedEntity::update(deltaTime, currentDirection);
}

void CharacterEntity::roundPosition() {
    setPosition(std::round(getPosition().x), std::round(getPosition().y));
}