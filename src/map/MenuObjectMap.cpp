#include "../../includes/map/MenuObjectMap.h"

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
        sf::FloatRect boundingBox = sf::FloatRect(object.getAABB().left, object.getAABB().top, object.getAABB().width, object.getAABB().height);

        switch(type) {
            case ObjectType::MENU: {
                playerMenu.initialize(object.getName(), type, boundingBox);
                break;
            }
            case ObjectType::MENU_OPTION: {
                MenuOptionComponent playerMenuOption;
                int index = std::stoi(object.getName()); //TODO: error handling if name is wrong
                playerMenuOption.initialize(object.getName(), type, boundingBox, index);
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