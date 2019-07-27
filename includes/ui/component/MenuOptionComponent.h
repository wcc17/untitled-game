#ifndef NEWNEW_MENUOPTIONCOMPONENT_H
#define NEWNEW_MENUOPTIONCOMPONENT_H


#include <SFML/Graphics/Text.hpp>
#include "UIComponent.h"

class MenuOptionComponent : public UIComponent, public sf::Text {

public:
    void initialize(std::string assetName, ObjectType type, sf::Vector2f initialPosition, int index);

    bool operator< (const MenuOptionComponent &other) const {
        return index < other.index;
    }

private:
    int index;

};


#endif //NEWNEW_MENUOPTIONCOMPONENT_H
