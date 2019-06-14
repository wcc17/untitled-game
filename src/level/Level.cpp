#include "../../includes/level/Level.h"

//TODO: can this just be one class (TileMap and Level)
void Level::initialize(std::string tileMapPath) {
    TileMap::initialize(tileMapPath);
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &texture;

    for(sf::VertexArray vertexArray : vertices) {
        target.draw(vertexArray, states);
    }
}