#include "../../../includes/ui/component/MenuOptionComponent.h"

void MenuOptionComponent::initialize(int index, std::string displayText, UIComponentType opensToMenu) {
    this->index = index;
    this->opensToMenu = opensToMenu;
    setString(displayText);
}

UIComponentType MenuOptionComponent::getOpensToMenu() {
    return this->opensToMenu;
}

int MenuOptionComponent::getIndex() {
    return this->index;
}

std::string MenuOptionComponent::getDisplayText() {
    return getString();
}