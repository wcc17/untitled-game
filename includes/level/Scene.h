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

class Scene : public sf::Drawable, public sf::Transformable, public ObjectMap, public TileMap {
public:
    void initialize(std::string tileMapPath);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void release();
    sf::Vector2f getMapSizeInPixels();

private:
    sf::Texture texture;
    sf::Vector2f mapSizeInPixels;
    std::string tileMapPath;

    void loadTileMap();
};


#endif //NEWNEW_SCENE_H
