#ifndef NEWNEW_MENUOPTIONCOMPONENT_H
#define NEWNEW_MENUOPTIONCOMPONENT_H


#include <SFML/Graphics/Text.hpp>
#include "../UIComponentType.h"

class MenuOptionComponent : public sf::Text {

public:
    void initialize(int index, std::string displayText, UIComponentType opensToMenu);
    UIComponentType getOpensToMenu();
    int getIndex();
    std::string getDisplayText();

    bool operator< (const MenuOptionComponent &other) const {
        return index < other.index;
    }

private:
    int index;
    UIComponentType opensToMenu;
};


#endif //NEWNEW_MENUOPTIONCOMPONENT_H
