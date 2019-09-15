#include "../../../../includes/ui/component/menu_component/DialogueMenuComponent.h"

void DialogueMenuComponent::updateMenuOption(std::string textToDraw) {
    //TODO: there should only ever be one menu option in DialogueMenuComponent, but error handling should still be here (or at least a log)
    menuOptions[0].setString(textToDraw);
}