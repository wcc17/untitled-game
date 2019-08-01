#include "../../includes/map/MenuMap.h"

MenuMap::MenuMap() : logger("MenuMap") {}

const std::string DISPLAY_TEXT_PROPERTY = "displayText";
const std::string OPENS_TO_MENU_PROPERTY = "opensToMenu";
const std::string IS_BASE_MENU_OPTION_PROPERTY = "isBaseMenuOption";

std::shared_ptr<MenuComponent> MenuMap::loadMenu(std::string menuName, const std::vector<tmx::Object> &objects) {
    std::shared_ptr<MenuComponent> menu;

    for(tmx::Object object : objects) {
        ObjectType type = determineObjectType(object.getType());

        std::string objectName = object.getName();
        sf::FloatRect boundingBox = sf::FloatRect(object.getAABB().left, object.getAABB().top, object.getAABB().width, object.getAABB().height);

        switch(type) {
            case ObjectType::MENU: {
                if(menuName == "party_menu") {
                    menu = std::make_shared<PartyMenuComponent>();
                } else {
                    menu = std::make_shared<MenuComponent>();
                }

                menu->initialize(object.getName(), type, boundingBox);
                break;
            }
            case ObjectType::MENU_OPTION: {
                MenuOptionComponent menuOption;
                int index = std::stoi(object.getName()); //TODO: error handling if name is wrong
                std::string displayText = getObjectPropertyStringValue(DISPLAY_TEXT_PROPERTY, object.getProperties());
                std::string opensToMenu = getObjectPropertyStringValue(OPENS_TO_MENU_PROPERTY, object.getProperties());
                bool isBaseMenuOption = getObjectPropertyBoolValue(IS_BASE_MENU_OPTION_PROPERTY, object.getProperties());

                menuOption.initialize(object.getName(), type, boundingBox, index, displayText, opensToMenu, isBaseMenuOption);
                menu->addMenuOption(menuOption);
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