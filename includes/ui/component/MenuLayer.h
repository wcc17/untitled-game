#ifndef NEWNEW_MENULAYER_H
#define NEWNEW_MENULAYER_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "MenuComponent.h"
#include "../../controller/MoveDirection.h"

class MenuLayer : public sf::Sprite {
public:
    void initialize(sf::Texture* menuSelectorTexture, sf::Font* font, float windowScale);
    void update(sf::RenderTexture& texture);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setMenuLayerPosition(sf::Vector2f& position, sf::RenderTexture& renderTexture);
    void addLayerVertices(std::string name, sf::VertexArray vertices);
    void addMenuComponent(std::string name, MenuComponent menuComponent);
    void moveSelector(MoveDirection direction);

private:
    void initializeMenuOptionsFont(sf::Font* font, float windowScale);
    void setSelectorPosition(sf::RenderTexture& renderTexture);

    std::map<std::string, sf::VertexArray> vertexArrayMap;
    std::map<std::string, MenuComponent> menuComponentMap;
    std::vector<sf::VertexArray> activeVertexArrays;
    MenuComponent activeMenuComponent;
    sf::Sprite menuSelector;
    bool shouldUpdateSelectorPosition = false;
};


#endif //NEWNEW_MENULAYER_H
