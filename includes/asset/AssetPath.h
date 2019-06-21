#ifndef NEWNEW_ASSETPATH_H
#define NEWNEW_ASSETPATH_H

#include <string>

class AssetPath {

public:
    enum AssetType {
        FONT, TEXTURE, TILEMAP
    };

    static const std::string OPENSANS_REGULAR;
    static const std::string OPENSANS_BOLD;
    static const std::string PLAYER_TEXTURE;
    static const std::string NPC_TEXTURE;
    static const std::string SCENE_TILEMAP;
    static const std::string DIALOGUE_BOX_TEXTURE;
};

#endif //NEWNEW_ASSETPATH_H
