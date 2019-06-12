#include "../../includes/level/Level.h"

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

//TODO: only passing player bounds for now, but will eventually want anything that could collide with something (so probably a vector of rects)
std::vector<Collidable> Level::handleCollisions(sf::FloatRect playerBounds) {
    std::vector<Collidable> collided;
    for(Collidable collidable : this->collidables) {
       if(collidable.getBoundingBox().intersects(playerBounds)) {
           collided.push_back(collidable);
       }
    }

    return collided;
}