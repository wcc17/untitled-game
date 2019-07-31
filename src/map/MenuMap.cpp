#include "../../includes/map/MenuMap.h"

MenuMap::MenuMap() : logger("MenuMap") {}

MenuComponent MenuMap::loadMenu(const std::vector<tmx::Object> &objects) {
    MenuComponent menu;
    for(tmx::Object object : objects) {
        ObjectType type = determineObjectType(object.getType());

        std::string objectName = object.getName();
        sf::FloatRect boundingBox = sf::FloatRect(object.getAABB().left, object.getAABB().top, object.getAABB().width, object.getAABB().height);

        switch(type) {
            case ObjectType::MENU: {
                menu.initialize(object.getName(), type, boundingBox);
                break;
            }
            case ObjectType::MENU_OPTION: {
                MenuOptionComponent menuOption;
                int index = std::stoi(object.getName()); //TODO: error handling if name is wrong
                std::string displayText = getObjectPropertyValue("displayText", object.getProperties());
                std::string opensToMenu = getObjectPropertyValue("opensToMenu", object.getProperties());

                menuOption.initialize(object.getName(), type, boundingBox, index, displayText, opensToMenu);
                menu.addMenuOption(menuOption);
                break;
            }
            default: {
                logger.logError("Trying to load something from menu object map that is not supported");
                break;
            }
        }
    }

    return menu;
}