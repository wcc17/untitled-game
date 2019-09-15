#ifndef NEWNEW_MENUCOMPONENT_H
#define NEWNEW_MENUCOMPONENT_H


#include <SFML/Graphics/RenderTarget.hpp>
#include "UIComponent.h"
#include "MenuOptionComponent.h"
#include "../../controller/MoveDirection.h"
#include "../../util/Logger.h"
#include "MenuScreenPosition.h"

class MenuComponent : public UIComponent {

public:
    MenuComponent();

    virtual void initialize(
            sf::Font* font,
            float windowScale,
            std::string name,
            ObjectType type,
            sf::Texture* texture,
            ScreenPosition screenPosition,
            sf::Vector2f textOffset);
    void addMenuOption(MenuOptionComponent menuOption);
    void drawToRenderTexture(sf::RenderTexture* renderTexture);
    virtual void updatePositionForView(sf::RenderTexture& renderTexture, sf::View& view);

    void changeActiveMenuOption(MoveDirection direction);
    sf::Vector2f getSelectorPositionBasedOnSelectedMenuOption(sf::Vector2f selectorDimensions);
    std::string getActiveMenuOptionNextMenu();

protected:
    std::vector<MenuOptionComponent> menuOptions;

private:
    Logger logger;

    sf::Font* font;
    sf::Sprite menuSprite;
    sf::Vector2f defaultTextOffset = sf::Vector2f(10, 5);
    sf::Vector2f textOffset;
    ScreenPosition screenPosition;
    float windowScale;
    int selectedMenuOptionIndex = 0;

    void sortMenuOptions();
    void updateMenuComponentTextPosition(sf::RenderTexture& renderTexture, sf::View& view, MenuOptionComponent& menuOptionComponent);
};


#endif //NEWNEW_MENUCOMPONENT_H
