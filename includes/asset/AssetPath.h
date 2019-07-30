#ifndef NEWNEW_ASSETPATH_H
#define NEWNEW_ASSETPATH_H

#include <string>
#include <map>

class AssetPath {

public:
    enum AssetType {
        FONT, TEXTURE, TILEMAP
    };

    static const std::string OPENSANS_REGULAR;
    static const std::string OPENSANS_BOLD;
    static const std::string MUNRO_NARROW;
    static const std::string MUNRO_REGULAR;
    static const std::string PLAYER_TEXTURE;
    static const std::string DIALOGUE_BOX_TEXTURE;
    static const std::string MENU_SELECTOR_TEXTURE;

    static std::string getSceneMapPath(std::string sceneName);
    static std::string getMenuLayerMapPath(std::string menuName);
    static std::string getNpcAssetPath(std::string npcName);
};

#endif //NEWNEW_ASSETPATH_H
