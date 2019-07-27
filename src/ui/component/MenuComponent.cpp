#include "../../../includes/ui/component/MenuComponent.h"

void MenuComponent::initializeMenuOptionFont(sf::Font* font, float windowScale) {

    //TODO: constants
    for(MenuOptionComponent& menuOption : menuOptions) {
        menuOption.setFillColor(sf::Color::Black);
        menuOption.setLineSpacing(1.f);
        menuOption.setFont(*font);
        menuOption.setCharacterSize(72 * windowScale);
    }
}

void MenuComponent::addMenuOption(MenuOptionComponent menuOption) {
    menuOptions.push_back(menuOption);
    sortMenuOptions();
}

void MenuComponent::sortMenuOptions() {
    std::sort(menuOptions.begin(), menuOptions.end());
}

void MenuComponent::setPositionRelativeToNewPosition(sf::Vector2f &newPosition, sf::RenderTexture& renderTexture) {
    sf::Vector2f componentPosition = sf::Vector2f(newPosition.x + initialPosition.x, newPosition.y + initialPosition.y);
    boundingBox.left = componentPosition.x;
    boundingBox.top = componentPosition.y;

    for(MenuOptionComponent& menuOption : menuOptions) {
        menuOption.setPositionRelativeToNewPosition(newPosition, renderTexture);
    }
}

void MenuComponent::changeActiveMenuOption(MoveDirection direction) {
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

sf::Vector2f MenuComponent::getSelectorPositionBasedOnSelectedMenuOption() {
    return menuOptions[selectedMenuOptionIndex].getPosition();
}

void MenuComponent::draw(sf::RenderTarget& renderTarget) const {
    sf::View oldView = renderTarget.getView();
    renderTarget.setView(renderTarget.getDefaultView());

    for(MenuOptionComponent menuOption : menuOptions) {
        renderTarget.draw(menuOption);
    }

    renderTarget.setView(oldView);
}
