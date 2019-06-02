//
// Created by William Curry on 2019-06-01.
//

#ifndef NEWNEW_TEXTUREMANAGER_H
#define NEWNEW_TEXTUREMANAGER_H


#include <SFML/Graphics/Texture.hpp>
#include "BaseAssetManager.h"

class TextureManager : public BaseAssetManager {

public:
    TextureManager();

    void loadTexture(std::string filename);
    sf::Texture* getTexture(std::string filename);
    void releaseTexture(std::string filename);
    void releaseTextures();

private:
    std::map<std::string, std::unique_ptr<sf::Texture>> textureMap;
};

#endif //NEWNEW_TEXTUREMANAGER_H
