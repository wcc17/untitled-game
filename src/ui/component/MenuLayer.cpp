#include "../../../includes/ui/component/MenuLayer.h"

//TODO: should this class be a part of UIComponentManager instead?

void MenuLayer::initialize(sf::Texture* menuSelectorTexture, sf::Font* font, float windowScale) {
    menuSelector.setTexture(*menuSelectorTexture);
    initializeMenuOptionsFont(font, windowScale);

    activeMenuComponent = menuComponentMap.at("player_menu"); //TODO: not the correct way to do this once I want to show/hide certain menus
    activeVertexArrays.push_back(vertexArrayMap.at("player_menu")); //TODO: not the correct way to do this once I want to show/hide certain menus
}

void MenuLayer::initializeMenuOptionsFont(sf::Font* font, float windowScale) {
    std::map<std::string, MenuComponent>::iterator it = menuComponentMap.begin();
    while (it != menuComponentMap.end()) {
        it->second.initializeMenuOptionFont(font, windowScale);
        it++;
    }
}

void MenuLayer::update(sf::RenderTexture& texture) {
    if(shouldUpdateSelectorPosition) {
        shouldUpdateSelectorPosition = false;
        setSelectorPosition(texture);
    }
}

void MenuLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = getTexture();

    for(sf::VertexArray vertexArray : activeVertexArrays) {
        target.draw(vertexArray, states);
    }

    activeMenuComponent.draw(target);
    target.draw(menuSelector);
}

void MenuLayer::setMenuLayerPosition(sf::Vector2f& position, sf::RenderTexture& renderTexture) {
    setPosition(position);
    activeMenuComponent.setPositionRelativeToNewPosition(position, renderTexture);

    setSelectorPosition(renderTexture);
}

void MenuLayer::setSelectorPosition(sf::RenderTexture& renderTexture) {
    sf::Vector2f selectorPosition = activeMenuComponent.getSelectorPositionBasedOnSelectedMenuOption();
    selectorPosition = renderTexture.mapPixelToCoords(sf::Vector2i(selectorPosition.x, selectorPosition.y));
    selectorPosition = sf::Vector2f(selectorPosition.x - menuSelector.getGlobalBounds().width, selectorPosition.y);
    menuSelector.setPosition(selectorPosition);
}

void MenuLayer::moveSelector(MoveDirection direction) {
    if(direction == MoveDirection::UP || direction == MoveDirection::DOWN) {
        activeMenuComponent.changeActiveMenuOption(direction);
        shouldUpdateSelectorPosition = true;
    }
}

void MenuLayer::addMenuComponent(std::string name, MenuComponent menuComponent) {
    menuComponentMap.insert(std::make_pair(name, menuComponent));
}

void MenuLayer::addLayerVertices(std::string name, sf::VertexArray vertices) {
    vertexArrayMap.insert(std::make_pair(name, vertices));
}