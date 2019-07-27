#include "../../../includes/ui/component/UIComponent.h"

void UIComponent::initialize(std::string name, ObjectType type, sf::Vector2f initialPosition) {
    this->name = name;
    this->type = type;
    this->initialPosition = initialPosition;
}

std::string UIComponent::getName() {
    return this->name;
}

ObjectType UIComponent::getType() {
    return this->type;
}

sf::Vector2f UIComponent::getInitialPosition() {
    return this->initialPosition;
}