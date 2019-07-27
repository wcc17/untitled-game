#ifndef NEWNEW_MENUCOMPONENT_H
#define NEWNEW_MENUCOMPONENT_H


#include <SFML/Graphics/RenderTarget.hpp>
#include "UIComponent.h"
#include "MenuOptionComponent.h"
#include "../../controller/MoveDirection.h"

class MenuComponent : public UIComponent {

public:
    void initializeMenuOptionFont(sf::Font* font, float windowScale);
    void addMenuOption(MenuOptionComponent menuOption);
    void setPositionRelativeToNewPosition(sf::Vector2f &newPosition, sf::RenderTexture& renderTexture);
    void draw(sf::RenderTarget& renderTarget) const;
    void changeActiveMenuOption(MoveDirection direction);
    sf::Vector2f getSelectorPositionBasedOnSelectedMenuOption();

private:
    std::vector<MenuOptionComponent> menuOptions;
    void sortMenuOptions();
    int selectedMenuOptionIndex = 0;
};


#endif //NEWNEW_MENUCOMPONENT_H
