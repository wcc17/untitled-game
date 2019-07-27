#include "../../../includes/ui/component/MenuOptionComponent.h"

void MenuOptionComponent::initialize(std::string name, ObjectType type, sf::FloatRect boundingBox, int index) {
    UIComponent::initialize(name, type, boundingBox);
    this->index = index;
}
