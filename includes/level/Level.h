#ifndef NEWNEW_LEVEL_H
#define NEWNEW_LEVEL_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <string>

class Level : public sf::Drawable, public sf::Transformable {
public:
    Level(float windowWidth, float windowHeight);
    sf::View getView() const;
    void update(sf::Time deltaTime);
    void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
    void stop();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::View view;
    sf::Vector2f movement;
    float speed;

    sf::Texture texture;
    std::vector<sf::VertexArray> vertices;

    void loadTileMap();
    void handleTileLayer(tmx::TileLayer layer, tmx::Tileset tileset, tmx::Vector2u mapSizeInTiles, tmx::Vector2u tileSize);
    bool isTileIdTransparent(uint32_t layerTileId);

    void resetMovement();
};


#endif //NEWNEW_LEVEL_H
