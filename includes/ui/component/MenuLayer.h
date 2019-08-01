#ifndef NEWNEW_MENULAYER_H
#define NEWNEW_MENULAYER_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "MenuComponent.h"
#include "../../controller/MoveDirection.h"
#include <stack>

class MenuLayer : public sf::Sprite {
public:
    void initialize(sf::Texture* menuSelectorTexture, sf::Font* font, float windowScale);
    void update(sf::RenderTexture& texture);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateMenuPositionsWithNewOriginPosition(sf::RenderTexture& renderTexture, sf::Vector2f newOriginPosition);
    void updateMenuPositions(sf::RenderTexture& renderTexture);
    void addLayerVertices(std::string name, sf::VertexArray vertices);
    void addMenuComponent(std::string name, std::shared_ptr<MenuComponent> menuComponent);
    void moveSelector(MoveDirection direction);
    void selectMenuOption();
    bool doesRootMenuHaveFocus();
    void closeCurrentMenuWithFocus();
    void closeRootMenu();
    void setTilesetImagePath(std::string path);
    void release(TextureManager& textureManager);

private:
    enum MenuLayerState {
        SELECTOR_POSITION_CHANGED,
        OPTION_SELECTED,
        NESTED_MENU_CLOSED,
        DEFAULT
    };
    MenuLayerState state = MenuLayerState::DEFAULT;

    std::map<std::string, sf::VertexArray> vertexArrayMap;
    std::map<std::string, std::shared_ptr<MenuComponent>> menuComponentMap;

    std::vector<sf::VertexArray> openMenuVertexArrays;
    std::shared_ptr<MenuComponent> menuComponentWithFocus;
    std::stack<std::shared_ptr<MenuComponent>> menuComponentBreadcrumbStack;
    std::vector<std::shared_ptr<MenuComponent>> openMenuComponents;

    sf::Sprite menuSelector;
    sf::Vector2f originPosition; //the "0, 0" position in the view that lines the menu texture up with the top left corner of the screen
    std::string tilesetImagePath;

    void initializeMenuOptionsFont(sf::Font* font, float windowScale);
    void updateSelectorPosition(sf::RenderTexture& renderTexture);
    void changeFocusMenu(std::string menuName);
};


#endif //NEWNEW_MENULAYER_H
