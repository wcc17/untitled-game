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
    static const std::string LEVEL_TILEMAP;
};

#endif //NEWNEW_ASSETPATH_H
