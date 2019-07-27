#ifndef NEWNEW_MENULAYER_H
#define NEWNEW_MENULAYER_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "MenuComponent.h"

class MenuLayer : public sf::Sprite {
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void addLayerVertices(std::string name, sf::VertexArray vertices);
    void addMenuComponent(std::string name, MenuComponent menuComponent);

private:
    std::map<std::string, sf::VertexArray> vertexArrayMap;
    std::map<std::string, MenuComponent> menuComponentMap;
    std::vector<sf::VertexArray> activeVertexArrays;
};


#endif //NEWNEW_MENULAYER_H
