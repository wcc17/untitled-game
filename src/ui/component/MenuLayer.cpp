#include "../../../includes/ui/component/MenuLayer.h"

//TODO: should this class be a part of UIComponentManager instead?

void MenuLayer::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* menuSelectorTexture, sf::Font* font, float windowScale) {
    this->eventBus = eventBus;

    menuSelector.setTexture(*menuSelectorTexture);
    initializeMenuOptionsFont(font, windowScale);

    changeFocusMenu("player_menu");
}

void MenuLayer::initializeMenuOptionsFont(sf::Font* font, float windowScale) {
    std::map<std::string, std::shared_ptr<MenuComponent>>::iterator it = menuComponentMap.begin();
    while (it != menuComponentMap.end()) {
        it->second->initializeMenuComponent(font, windowScale);
        it++;
    }
}

void MenuLayer::update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime) {
    switch(state) {
        case ACTIVE:
            break;
        case INACTIVE:
            break;
        case READY:
            updateComponentOriginPosition(renderTexture, view);
            break;
        case SELECTOR_POSITION_CHANGED:
            updateSelectorPosition(renderTexture);
            break;
        case OPTION_SELECTED:
            updateMenuPositions(renderTexture);
            break;
        case NESTED_MENU_CLOSED:
            updateSelectorPosition(renderTexture);
            break;
        case DEFAULT:
            break;
    }

//    state = DEFAULT; //TODO: why was this needed? is it still needed?
}

void MenuLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = getTexture();

    for(sf::VertexArray vertexArray : openMenuVertexArrays) {
        target.draw(vertexArray, states);
    }

    for(int i = 0; i < openMenuComponents.size(); i++) {
        openMenuComponents[i]->draw(target);
    }

    target.draw(menuSelector);
}

void MenuLayer::updateMenuPositions(sf::RenderTexture& renderTexture) {
    setPosition(originPosition);

    for(int i = 0; i < openMenuComponents.size(); i++) {
        openMenuComponents[i]->setPositionRelativeToNewPosition(originPosition, renderTexture);
    }

    updateSelectorPosition(renderTexture);
}

void MenuLayer::updateMenuPositionsWithNewOriginPosition(sf::RenderTexture& renderTexture, sf::Vector2f newOriginPosition) {
    this->originPosition = newOriginPosition;
    updateMenuPositions(renderTexture);
}

void MenuLayer::updateSelectorPosition(sf::RenderTexture& renderTexture) {
    sf::Vector2f selectorPosition = menuComponentWithFocus->getSelectorPositionBasedOnSelectedMenuOption();
    selectorPosition = renderTexture.mapPixelToCoords(sf::Vector2i(selectorPosition.x, selectorPosition.y));
    selectorPosition = sf::Vector2f(selectorPosition.x - menuSelector.getGlobalBounds().width, selectorPosition.y);
    menuSelector.setPosition(selectorPosition);
}

void MenuLayer::moveSelector(MoveDirection direction) {
    if(direction == MoveDirection::UP || direction == MoveDirection::DOWN) {
        menuComponentWithFocus->changeActiveMenuOption(direction);
        state = MenuLayerState::SELECTOR_POSITION_CHANGED;
    }
}

void MenuLayer::selectMenuOption() {
    std::string menuToOpen = menuComponentWithFocus->getActiveMenuOptionNextMenu();
    if(menuToOpen != "") {
        changeFocusMenu(menuToOpen);
        state = MenuLayerState::OPTION_SELECTED;
    }
}

void MenuLayer::changeFocusMenu(std::string menuName) {
    menuComponentWithFocus = menuComponentMap.at(menuName);
    menuComponentBreadcrumbStack.push(menuComponentMap.at(menuName));
    openMenuComponents.push_back(menuComponentMap.at(menuName));
    openMenuVertexArrays.push_back(vertexArrayMap.at(menuName));
}

bool MenuLayer::doesRootMenuHaveFocus() {
    return (openMenuComponents.size() <= 1);
}

void MenuLayer::closeCurrentMenuWithFocus() {
    menuComponentWithFocus->resetSelectedMenuOptionIndex(); //reset the selector position
    menuComponentBreadcrumbStack.pop(); //remove the current one from the stack

    std::shared_ptr<MenuComponent> menuToClose = menuComponentWithFocus;
    menuComponentWithFocus = menuComponentBreadcrumbStack.top();

    //remove the menu we're closing from openMenuComponents
    auto it = openMenuComponents.begin();
    while (it != openMenuComponents.end())
    {
        if (it->get()->getName() == menuToClose->getName()) {
            // erase() invalidates the iterator, use returned iterator
            it = openMenuComponents.erase(it);
        } else {
            ++it;
        }
    }

    openMenuVertexArrays.clear();
    for(int i = 0; i < openMenuComponents.size(); i++) {
        openMenuVertexArrays.push_back(vertexArrayMap.at(openMenuComponents[i]->getName()));
    }

    state = MenuLayerState::NESTED_MENU_CLOSED;
}

void MenuLayer::closeRootMenu() {
    menuComponentWithFocus->resetSelectedMenuOptionIndex();
}

void MenuLayer::addMenuComponent(std::string name, std::shared_ptr<MenuComponent> menuComponent) {
    menuComponentMap.insert(std::make_pair(name, menuComponent));
}

void MenuLayer::addLayerVertices(std::string name, sf::VertexArray vertices) {
    vertexArrayMap.insert(std::make_pair(name, vertices));
}

void MenuLayer::setTilesetImagePath(std::string path) {
    this->tilesetImagePath = path;
}

void MenuLayer::release(TextureManager& textureManager) {
    textureManager.releaseTexture(tilesetImagePath);
}