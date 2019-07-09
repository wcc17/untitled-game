#include "../../includes/asset/AssetPath.h"

const std::string AssetPath::OPENSANS_REGULAR = "assets/fonts/OpenSans-Regular.ttf";
const std::string AssetPath::OPENSANS_BOLD = "assets/fonts/OpenSans-Bold.ttf";
const std::string AssetPath::MUNRO_NARROW = "assets/fonts/munro-narrow.ttf";
const std::string AssetPath::MUNRO_REGULAR = "assets/fonts/munro.ttf";

//const std::string AssetPath::PLAYER_TEXTURE = "assets/gfx/character_cropped.png";
const std::string AssetPath::PLAYER_TEXTURE = "assets/gfx/entity/player.png";

//const std::string AssetPath::NPC_TEXTURE = "assets/gfx/npc_cropped.png";
const std::string AssetPath::NPC_TEXTURE = "assets/gfx/entity/npc1.png";

const std::string AssetPath::DIALOGUE_BOX_TEXTURE = "assets/gfx/dialogue_box.png";

std::string AssetPath::getSceneMapPath(std::string sceneName) {
    return "assets/gfx/tileset/" + sceneName + "_map.tmx";
}