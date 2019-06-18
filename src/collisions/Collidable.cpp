#include "../../includes/collisions/Collidable.h"

Collidable::Collidable() {
    this->name = "";
    this->type = CollidableType::NO_TYPE;
    this->boundingBox = sf::FloatRect({0.f, 0.f, 0.f, 0.f});
}

Collidable::Collidable(std::string name, CollidableType type, sf::Vector2f position, sf::Vector2f size) : boundingBox(position, size) {
    this->name = name;
    this->type = type;
}

void Collidable::updateBoundingBox(sf::FloatRect newBounds) {
    this->boundingBox = newBounds;
}

std::string Collidable::getName() {
    return this->name;
}

CollidableType Collidable::getType() {
    return this->type;
}

sf::FloatRect Collidable::getBoundingBox() {
    return this->boundingBox;
}

