#ifndef NEWNEW_MENUCOMPONENT_H
#define NEWNEW_MENUCOMPONENT_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "UIComponent.h"
#include "MenuOptionComponent.h"

class MenuComponent : public UIComponent, public sf::Sprite {

public:
    void initialize(std::string assetName, ObjectType type, sf::Vector2f initialPosition);
    void addMenuOption(MenuOptionComponent menuOption);
    void setComponentTexture(sf::Texture* texture, std::vector<sf::VertexArray> vertices);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::vector<MenuOptionComponent> menuOptions;
    void sortMenuOptions();
    std::vector<sf::VertexArray> vertices;

};


#endif //NEWNEW_MENUCOMPONENT_H
