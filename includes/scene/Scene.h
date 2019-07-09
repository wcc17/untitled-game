#ifndef NEWNEW_SCENE_H
#define NEWNEW_SCENE_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <tmxlite/Map.hpp>
#include <cmath>
#include "TileMap.h"
#include "ObjectMap.h"
#include "../util/Logger.h"
#include "../asset/AssetPath.h"

class Scene : public sf::Drawable, public sf::Transformable, public ObjectMap, public TileMap {
public:
    void initialize(std::string sceneName);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void release();
    sf::Vector2u getMapSizeInPixels();
    sf::Vector2u getMapSizeInTiles();
    sf::Vector2u getMapTileSize();

private:
    std::string sceneName;
    sf::Texture texture;
    sf::Vector2u mapSizeInPixels;
    sf::Vector2u mapSizeInTiles;
    sf::Vector2u tileSize;

    void loadTileMap();
    static Logger logger;
};


#endif //NEWNEW_SCENE_H
