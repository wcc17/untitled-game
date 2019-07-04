#include "../../includes/collisions/Collidable.h"

Collidable::Collidable() {
    this->name = "";
    this->type = ObjectType::NO_TYPE;
    this->boundingBox = sf::FloatRect({0.f, 0.f, 0.f, 0.f});
}

Collidable::Collidable(std::string name, ObjectType type, sf::Vector2f position, sf::Vector2f size) : boundingBox(position, size) {
    this->name = name;
    this->type = type;
}

std::string Collidable::getName() const {
    return this->name;
}

void Collidable::setName(std::string name) {
    this->name = name;
}

ObjectType Collidable::getType() const {
    return this->type;
}

void Collidable::setType(ObjectType type) {
    this->type = type;
}

sf::FloatRect Collidable::getBoundingBox() const {
    return this->boundingBox;
}

void Collidable::setBoundingBox(sf::FloatRect boundingBox) {
    this->boundingBox = boundingBox;
}
