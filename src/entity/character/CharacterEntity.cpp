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

void CharacterEntity::roundPosition() {
    setPosition(std::round(getPosition().x), std::round(getPosition().y));
}