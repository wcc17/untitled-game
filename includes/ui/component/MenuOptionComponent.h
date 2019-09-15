#ifndef NEWNEW_MENUOPTIONCOMPONENT_H
#define NEWNEW_MENUOPTIONCOMPONENT_H


#include <SFML/Graphics/Text.hpp>
#include "UIComponent.h"

class MenuOptionComponent : public UIComponent, public sf::Text {

public:
    void initialize(std::string name, ObjectType type, int index,
            std::string displayText, std::string opensToMenu);
    std::string getOpensToMenu();
    int getIndex();

    bool operator< (const MenuOptionComponent &other) const {
        return index < other.index;
    }

private:
    int index;
    std::string opensToMenu;
};


#endif //NEWNEW_MENUOPTIONCOMPONENT_H
