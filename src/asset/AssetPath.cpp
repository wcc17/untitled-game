#include "../../includes/asset/AssetPath.h"

const std::string AssetPath::OPENSANS_REGULAR = "assets/fonts/OpenSans-Regular.ttf";
const std::string AssetPath::OPENSANS_BOLD = "assets/fonts/OpenSans-Bold.ttf";
const std::string AssetPath::MUNRO_NARROW = "assets/fonts/munro-narrow.ttf";
const std::string AssetPath::MUNRO_REGULAR = "assets/fonts/munro.ttf";

const std::string AssetPath::PLAYER_TEXTURE = "assets/gfx/entity/player.png";
const std::string AssetPath::DIALOGUE_BOX_TEXTURE = "assets/gfx/dialogue_box.png";
const std::string AssetPath::MENU_SELECTOR_TEXTURE = "assets/gfx/ui/menu_selector.png";

std::string AssetPath::getSceneMapPath(std::string sceneName) {
    return "assets/gfx/tileset/" + sceneName + "_map.tmx";
}

std::string AssetPath::getNpcAssetPath(std::string npcName) {
    return "assets/gfx/entity/" + npcName + ".png";
}

std::string AssetPath::getUIComponentAssetPath(std::string componentName) {
    return "assets/gfx/ui/" + componentName + ".png";
}