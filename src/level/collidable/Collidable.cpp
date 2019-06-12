#include "../../../includes/level/collidable/Collidable.h"

Collidable::Collidable(sf::Vector2f position, sf::Vector2f size, std::string name, CollidableType type): boundingBox(position, size) {
    this->collidableName = name;
    this->type = type;
}

CollidableType Collidable::getType() {
    return this->type;
}

sf::FloatRect Collidable::getBoundingBox() {
    return this->boundingBox;
}