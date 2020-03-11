#include "../../../../includes/ui/component/menu_component/MenuWithSelectorComponent.h"

void MenuWithSelectorComponent::initializeMenuWithSelectorComponent(
        sf::Font *font,
        float windowScale,
        sf::Texture *componentTexture,
        sf::Texture *selectorTexture,
        ScreenPosition screenPosition,
        UIComponentType componentType) {
    BaseMenuComponent::initialize(font, windowScale, componentTexture, screenPosition, componentType);
    this->menuSelectorSprite.setTexture(*selectorTexture);
    this->textOffset = sf::Vector2f(menuSelectorSprite.getGlobalBounds().width, 0);
}

void MenuWithSelectorComponent::update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime) {
    BaseMenuComponent::update(renderTexture, view, deltaTime);
    updateSelectorPositionBasedOnMenuComponent();
}

void MenuWithSelectorComponent::drawToRenderTexture(sf::RenderTexture *renderTexture) {
    BaseMenuComponent::drawToRenderTexture(renderTexture);
    renderTexture->draw(menuSelectorSprite);
}

void MenuWithSelectorComponent::updateSelectorPositionBasedOnMenuComponent() {
    menuSelectorSprite.setPosition(getSelectorPositionBasedOnSelectedMenuOption());
}

void MenuWithSelectorComponent::changeActiveMenuOption(MoveDirection direction) {

    if(direction == MoveDirection::UP || direction == MoveDirection::DOWN) {
        if(direction == MoveDirection::UP) {
            selectedMenuOptionIndex--;
            if(selectedMenuOptionIndex < 0) {
                selectedMenuOptionIndex = menuOptions.size() - 1;
            }
        }

        if(direction == MoveDirection::DOWN) {
            selectedMenuOptionIndex++;
            if(selectedMenuOptionIndex > (menuOptions.size() - 1)) {
                selectedMenuOptionIndex = 0;
            }
        }
    }
}

std::string MenuWithSelectorComponent::getActiveMenuOptionName() {
    if(menuOptions.size() > 0) {
        return menuOptions[selectedMenuOptionIndex].getDisplayText();
    }

    return "";
}

sf::Vector2f MenuWithSelectorComponent::getSelectorPositionBasedOnSelectedMenuOption() {
    float height = menuSprite.getGlobalBounds().height / menuOptions.size();
    float x = defaultTextOffset.x;
    float y = defaultTextOffset.y + (height * selectedMenuOptionIndex);

    x += menuSprite.getPosition().x;
    y += menuSprite.getPosition().y;

    return sf::Vector2f(x, y);
}

void MenuWithSelectorComponent::handleControllerMenuMoveButtonPressed(MoveDirection direction) {
    changeActiveMenuOption(direction);
}