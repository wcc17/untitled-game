#include "../../../includes/ui/component/MenuOptionComponent.h"

void MenuOptionComponent::initialize(std::string assetName, ObjectType type, sf::Vector2f initialPosition, int index) {
    UIComponent::initialize(assetName, type, initialPosition);
    setPosition(initialPosition);
    this->index = index;
}
