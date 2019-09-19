#ifndef NEWNEW_ASSETPATH_H
#define NEWNEW_ASSETPATH_H

#include <string>
#include <map>
#include "../ui/UIComponentType.h"

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

    static std::string getSceneMapPath(std::string sceneName);
    static std::string getUIComponentAssetPath(UIComponentType componentType);
    static std::string getNpcAssetPath(std::string npcName);
};

#endif //NEWNEW_ASSETPATH_H
