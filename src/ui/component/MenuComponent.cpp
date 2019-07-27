#include "../../../includes/ui/component/MenuComponent.h"

void MenuComponent::initialize(std::string assetName, ObjectType type, sf::Vector2f initialPosition) {
    UIComponent::initialize(assetName, type, initialPosition);
    setPosition(initialPosition);
}

void MenuComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = getTexture();

    for(sf::VertexArray vertexArray : vertices) {
        target.draw(vertexArray, states);
    }
}

void MenuComponent::setComponentTexture(sf::Texture* texture, std::vector<sf::VertexArray> vertices) {
    setTexture(*texture);
    this->vertices = vertices;
}

void MenuComponent::addMenuOption(MenuOptionComponent menuOption) {
    menuOptions.push_back(menuOption);
    sortMenuOptions();
}

void MenuComponent::sortMenuOptions() {
    std::sort(menuOptions.begin(), menuOptions.end());
}
