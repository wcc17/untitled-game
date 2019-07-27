#include "../../../includes/ui/component/MenuLayer.h"

void MenuLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = getTexture();

    for(sf::VertexArray vertexArray : activeVertexArrays) {
        target.draw(vertexArray, states);
    }
}

void MenuLayer::addMenuComponent(std::string name, MenuComponent menuComponent) {
    menuComponentMap.insert(std::make_pair(name, menuComponent));
}

void MenuLayer::addLayerVertices(std::string name, sf::VertexArray vertices) {
    vertexArrayMap.insert(std::make_pair(name, vertices));
    activeVertexArrays.push_back(vertices); //TODO: not the correct way to do this once I want to show/hide certain menus
}