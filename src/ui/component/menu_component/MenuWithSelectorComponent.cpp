#include "../../../../includes/ui/component/menu_component/MenuWithSelectorComponent.h"

void MenuWithSelectorComponent::initialize(
        std::shared_ptr<EventBus> eventBus,
        sf::Font* font,
        float windowScale,
        sf::Texture* componentTexture,
        sf::Texture* selectorTexture,
        ScreenPosition screenPosition) {
    BaseMenuComponent::initialize(eventBus, font, windowScale, componentTexture, screenPosition);
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
    sf::Vector2f selectorDimensions = sf::Vector2f(
            menuSelectorSprite.getGlobalBounds().width,
            menuSelectorSprite.getGlobalBounds().height);
    menuSelectorSprite.setPosition(getSelectorPositionBasedOnSelectedMenuOption(selectorDimensions));
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

UIComponentType MenuWithSelectorComponent::getActiveMenuOptionNextMenu() {
    if(menuOptions.size() > 0) {
        return menuOptions[selectedMenuOptionIndex].getOpensToMenu();
    }

    return UIComponentType::NO_COMPONENT_TYPE; //TODO: how is this handled? is it even?
}

sf::Vector2f MenuWithSelectorComponent::getSelectorPositionBasedOnSelectedMenuOption(sf::Vector2f selectorDimensions) {
    float height = menuSprite.getGlobalBounds().height / menuOptions.size();
    float x = defaultTextOffset.x;
    float y = defaultTextOffset.y + (height * selectedMenuOptionIndex);

    x += menuSprite.getPosition().x;
    y += menuSprite.getPosition().y;

    return sf::Vector2f(x, y);
}

//TODO: I'm not sure that onControllerMenuEvent should be here in the component, in the UIManager makes more sense
void MenuWithSelectorComponent::onControllerMenuEvent(ControllerMenuEvent* event) {
    //TODO: OpenMenuEvent should have the name of the menu we actually want to open
    eventBus->publish(new OpenMenuEvent(UIComponentType::START_MENU));
}

void MenuWithSelectorComponent::onControllerActionEvent(ControllerActionEvent* event) {
    //TODO: open the menu thats stored in the "opensTo" variable on the selected menu option. Probably will publish an OpenMenuEvent like onControllerMenuEvent
    eventBus->publish(new OpenMenuEvent(getActiveMenuOptionNextMenu()));
}

void MenuWithSelectorComponent::onControllerMenuMoveEvent(ControllerMenuMoveEvent* event) {
    changeActiveMenuOption(event->direction);
}

void MenuWithSelectorComponent::onControllerCancelEvent(ControllerCancelEvent* event) {
    eventBus->publish(new CloseMenuEvent());
}