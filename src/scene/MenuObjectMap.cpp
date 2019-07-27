#include "../../includes/scene/MenuObjectMap.h"

MenuObjectMap::MenuObjectMap() : logger("MenuObjectMap") {}

void MenuObjectMap::loadObjectLayer(const tmx::ObjectGroup& layer) {
    std::string layerName = layer.getName();

    if(layerName == "player_menu") {
        loadPlayerMenu(layer.getObjects());
    }
}

void MenuObjectMap::loadPlayerMenu(const std::vector<tmx::Object> &objects) {
    for(tmx::Object object : objects) {
        ObjectType type = determineObjectType(object.getType());

        std::string objectName = object.getName();
        tmx::FloatRect boundingBox = object.getAABB();
        sf::Vector2f position(boundingBox.left, boundingBox.top);

        switch(type) {
            case ObjectType::MENU: {
                playerMenu.initialize(object.getName(), type, position);
                break;
            }
            case ObjectType::MENU_OPTION: {
                MenuOptionComponent playerMenuOption;
                int index = std::stoi(object.getName()); //TODO: error handling if name is wrong
                playerMenuOption.initialize(object.getName(), type, position, index);
                playerMenu.addMenuOption(playerMenuOption);
                break;
            }
            default: {
                logger.logError("Trying to load something from menu object map that is not supported");
                break;
            }
        }
    }
}

MenuComponent MenuObjectMap::getPlayerMenuComponent() {
    return this->playerMenu;
}