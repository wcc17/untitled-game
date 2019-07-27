#include "../../../includes/ui/component/MenuComponent.h"

void MenuComponent::addMenuOption(MenuOptionComponent menuOption) {
    menuOptions.push_back(menuOption);
    sortMenuOptions();
}

void MenuComponent::sortMenuOptions() {
    std::sort(menuOptions.begin(), menuOptions.end());
}
