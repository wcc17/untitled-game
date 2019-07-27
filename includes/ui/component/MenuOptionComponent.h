#ifndef NEWNEW_MENUOPTIONCOMPONENT_H
#define NEWNEW_MENUOPTIONCOMPONENT_H


#include <SFML/Graphics/Text.hpp>
#include "UIComponent.h"

class MenuOptionComponent : public UIComponent, public sf::Text {

public:
    void initialize(std::string name, ObjectType type, sf::FloatRect boundingBox, int index, std::string displayText);
    void setPositionRelativeToNewPosition(sf::Vector2f& newPosition, sf::RenderTexture& renderTexture);

    bool operator< (const MenuOptionComponent &other) const {
        return index < other.index;
    }

private:
    int index;

};


#endif //NEWNEW_MENUOPTIONCOMPONENT_H
