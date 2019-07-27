#ifndef NEWNEW_MENUCOMPONENT_H
#define NEWNEW_MENUCOMPONENT_H


#include "UIComponent.h"
#include "MenuOptionComponent.h"

class MenuComponent : public UIComponent {

public:
    void addMenuOption(MenuOptionComponent menuOption);

private:
    std::vector<MenuOptionComponent> menuOptions;
    void sortMenuOptions();

};


#endif //NEWNEW_MENUCOMPONENT_H
