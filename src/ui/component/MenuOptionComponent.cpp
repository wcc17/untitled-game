#include "../../../includes/ui/component/MenuOptionComponent.h"

void MenuOptionComponent::initialize(std::string name, ObjectType type,
        int index, std::string displayText, std::string opensToMenu) {
    UIComponent::initialize(name, type);
    this->index = index;
    this->opensToMenu = opensToMenu;
    setString(displayText);
}

std::string MenuOptionComponent::getOpensToMenu() {
    return this->opensToMenu;
}

int MenuOptionComponent::getIndex() {
    return this->index;
}