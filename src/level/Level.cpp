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

std::vector<Collidable> Level::handleCollisions() {
    std::vector<Collidable> collided;
    for(Collidable collidable : this->collidables) {
//        if(collidable.getBoundingBox().intersects(mybutt)) {
//            collided.push_back()
//        }
    }

    return collided;
}