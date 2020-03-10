#include "../../../includes/ui/component/MenuOptionComponent.h"

void MenuOptionComponent::initialize(int index, std::string displayText) {
    this->index = index;
    setString(displayText);
}

int MenuOptionComponent::getIndex() {
    return this->index;
}

std::string MenuOptionComponent::getDisplayText() {
    return getString();
}