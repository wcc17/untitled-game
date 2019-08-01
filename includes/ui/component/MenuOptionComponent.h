#ifndef NEWNEW_MENUOPTIONCOMPONENT_H
#define NEWNEW_MENUOPTIONCOMPONENT_H


#include <SFML/Graphics/Text.hpp>
#include "UIComponent.h"

class MenuOptionComponent : public UIComponent, public sf::Text {

public:
    void initialize(std::string name, ObjectType type, sf::FloatRect boundingBox, int index,
            std::string displayText, std::string opensToMenu, bool isBaseMenuOption);
    void setPositionRelativeToNewPosition(sf::Vector2f& newPosition, sf::RenderTexture& renderTexture);
    std::string getOpensToMenu();
    bool getIsBaseMenuOption();

    bool operator< (const MenuOptionComponent &other) const {
        return index < other.index;
    }

private:
    int index;
    std::string opensToMenu;
    bool isBaseMenuOption;

};


#endif //NEWNEW_MENUOPTIONCOMPONENT_H
