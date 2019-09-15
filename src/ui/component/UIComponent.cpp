#include "../../../includes/ui/component/UIComponent.h"

void UIComponent::initialize(std::string name, ObjectType type) {
    this->name = name;
    this->type = type;
}

std::string UIComponent::getName() {
    return this->name;
}

ObjectType UIComponent::getType() {
    return this->type;
}