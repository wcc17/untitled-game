#include "../../../includes/ui/component/MenuComponent.h"

MenuComponent::MenuComponent() : logger("MenuComponent") {};

void MenuComponent::initialize(
        sf::Font* font,
        float windowScale,
        std::string name,
        ObjectType type,
        sf::Texture* texture,
        ScreenPosition screenPosition,
        sf::Vector2f textOffset) {
    UIComponent::initialize(name, type);

    this->font = font;
    this->windowScale = windowScale;
    this->screenPosition = screenPosition;
    this->textOffset = textOffset;
    menuSprite.setTexture(*texture);
}

void MenuComponent::addMenuOption(MenuOptionComponent menuOption) {
    menuOption.setFillColor(sf::Color::Black);
    menuOption.setLineSpacing(1.f);
    menuOption.setFont(*font);
    menuOption.setCharacterSize(72 * windowScale);

    menuOptions.push_back(menuOption);
    sortMenuOptions();
}

void MenuComponent::sortMenuOptions() {
    std::sort(menuOptions.begin(), menuOptions.end());
}

void MenuComponent::changeActiveMenuOption(MoveDirection direction) {

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

std::string MenuComponent::getActiveMenuOptionNextMenu() {
    if(menuOptions.size() > 0) {
        return menuOptions[selectedMenuOptionIndex].getOpensToMenu();
    }

    return ""; //TODO: how is this handled? is it even?
}

sf::Vector2f MenuComponent::getSelectorPositionBasedOnSelectedMenuOption(sf::Vector2f selectorDimensions) {
    float height = menuSprite.getGlobalBounds().height / menuOptions.size();
    float x = defaultTextOffset.x;
    float y = defaultTextOffset.y + (height * selectedMenuOptionIndex);

    sf::Vector2f pos = menuSprite.getPosition();

    x += menuSprite.getPosition().x;
    y += menuSprite.getPosition().y;

    return sf::Vector2f(x, y);
}

void MenuComponent::updatePositionForView(sf::RenderTexture& renderTexture, sf::View& view) {
    float menuComponentX = 0;
    float menuComponentY = 0;

    switch(screenPosition) {
        case TOP_LEFT:
            menuComponentX = view.getCenter().x - (view.getSize().x / 2);
            menuComponentY = view.getCenter().y - (view.getSize().y / 2);
            break;
        case TOP_RIGHT:
            menuComponentX = view.getCenter().x + (view.getSize().x / 2) - (menuSprite.getTextureRect().width);
            menuComponentY = view.getCenter().y - (view.getSize().y / 2);
            break;
        case BOTTOM_LEFT:
            menuComponentX = view.getCenter().x - (view.getSize().x / 2);
            menuComponentY = view.getCenter().y + (view.getSize().y / 2) - (menuSprite.getTextureRect().height);
            break;
        case BOTTOM_RIGHT:
            menuComponentX = view.getCenter().x + (view.getSize().x / 2) + (menuSprite.getTextureRect().width);
            menuComponentY = view.getCenter().y - (view.getSize().y / 2) - (menuSprite.getTextureRect().height);
            break;
        case CENTERED:
            break;
    }

    menuSprite.setPosition(menuComponentX, menuComponentY);

    for(MenuOptionComponent menuOptionComponent : menuOptions) {
        for (int i = 0; i < menuOptions.size(); i++) {
            updateMenuComponentTextPosition(renderTexture, view, menuOptions[i]);
        }
    }
}

void MenuComponent::updateMenuComponentTextPosition(sf::RenderTexture& renderTexture, sf::View& view, MenuOptionComponent& menuOptionComponent) {
    float x = menuSprite.getPosition().x;
    float y = menuSprite.getPosition().y + (menuOptionComponent.getIndex() * (menuSprite.getGlobalBounds().height / (menuOptions.size())));

    x += (defaultTextOffset.x + textOffset.x);
    y += (defaultTextOffset.y + textOffset.y);

    sf::Vector2i coordsToPixel = renderTexture.mapCoordsToPixel(sf::Vector2f(x, y), view);
    menuOptionComponent.setPosition(sf::Vector2f(coordsToPixel.x, coordsToPixel.y));
}

void MenuComponent::drawToRenderTexture(sf::RenderTexture *renderTexture) {
    renderTexture->draw(menuSprite);

    sf::View originalView = renderTexture->getView();
    renderTexture->setView(renderTexture->getDefaultView());
    for(MenuOptionComponent menuOptionComponent : menuOptions) {
        sf::Vector2f position = menuOptionComponent.getPosition();
        renderTexture->draw(menuOptionComponent);
    }
    renderTexture->setView(originalView);
}