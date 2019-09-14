#ifndef NEWNEW_TEXTUREMANAGER_H
#define NEWNEW_TEXTUREMANAGER_H


#include <SFML/Graphics/Texture.hpp>
#include "BaseAssetManager.h"
#include <memory>

class TextureManager : public BaseAssetManager {

public:
    TextureManager();

    void loadTexture(std::string filename);
    sf::Texture* getTexture(std::string filename);
    void releaseTexture(std::string filename);

private:
    std::map<std::string, std::unique_ptr<sf::Texture>> textureMap;
};

#endif //NEWNEW_TEXTUREMANAGER_H
