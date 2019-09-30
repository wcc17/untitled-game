#include "../../includes/asset/AssetPath.h"
#include "../../includes/ui/UIComponentType.h"

const std::string AssetPath::OPENSANS_REGULAR = "assets/fonts/OpenSans-Regular.ttf";
const std::string AssetPath::OPENSANS_BOLD = "assets/fonts/OpenSans-Bold.ttf";
const std::string AssetPath::MUNRO_NARROW = "assets/fonts/munro-narrow.ttf";
const std::string AssetPath::MUNRO_REGULAR = "assets/fonts/munro.ttf";

//ENTITY
const std::string AssetPath::PLAYER_TEXTURE = "assets/gfx/entity/player.png";

std::string AssetPath::getSceneMapPath(std::string sceneName) {
    return "assets/gfx/tileset/" + sceneName + "_map.tmx";
}

std::string AssetPath::getNpcAssetPath(std::string npcName) {
    return "assets/gfx/entity/" + npcName + ".png";
}

std::string AssetPath::getUIComponentAssetPath(UIComponentType componentType) {
    std::string componentName = "";

    switch(componentType) {
        case DIALOGUE_MENU:
            componentName = "dialogue_menu";
            break;
        case START_MENU:
            componentName = "start_menu";
            break;
        case MENU_SELECTOR:
            componentName = "menu_selector";
            break;
        case PARTY_MENU:
            componentName = "party_menu";
            break;
        default:
            componentName = "invalid_component_type";
            break;
    }
    return "assets/gfx/ui/" + componentName + ".png";
}