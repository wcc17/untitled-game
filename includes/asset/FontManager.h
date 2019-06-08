#ifndef NEWNEW_FONTMANAGER_H
#define NEWNEW_FONTMANAGER_H

#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include "BaseAssetManager.h"
#include "../../includes/asset/AssetPath.h"

class FontManager : public BaseAssetManager {

public:
    FontManager();

    void loadFont(std::string filename);
    sf::Font* getFont(std::string filename);
    void releaseFont(std::string filename);
    void releaseFonts();

private:
    std::map<std::string, std::unique_ptr<sf::Font>> fontMap;
};


#endif //NEWNEW_FONTMANAGER_H
