#include "../../includes/level/Level.h"

//TODO: should be called Scene instead
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

void Level::release() {
    TileMap::release();
}