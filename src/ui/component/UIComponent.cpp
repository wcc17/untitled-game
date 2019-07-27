#include "../../../includes/ui/component/UIComponent.h"

void UIComponent::initialize(std::string name, ObjectType type, sf::FloatRect boundingBox) {
    this->name = name;
    this->type = type;
    this->boundingBox = boundingBox;
    this->initialPosition = sf::Vector2f(boundingBox.left, boundingBox.top);
}

std::string UIComponent::getName() {
    return this->name;
}

ObjectType UIComponent::getType() {
    return this->type;
}

sf::FloatRect UIComponent::getBoundingBox() {
    return this->boundingBox;
}