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

void Level::update(sf::Time deltaTime) {
    //TODO: don't maybe level shouldn't have a .update() function, just handleCollisisions and anything else it might need to do
}

void Level::handleCollisions() {
    for(Collidable collidable : this->collidables) {
//        if(collidable.getBoundingBox().intersects(mybutt)) {
        /**
            * NOTE: on type. For now, these will all do pretty much the same thing
            * Eventually, there will be objects that inherit from Collidable and they will all be in the "collidables" vector
            * We can handle what to do with them in their own methods from here
            * Checking a type variable instead of object type on purpose. This is more precise and it doesn't change anything
            * This will eventually be doing a lot. Could potentially handle collisions in a LevelManager or GameManager or something like that.
         */
            switch(collidable.getType()) {
                case CollidableType::NO_TYPE:
                    handleNoTypeCollision();
                    break;
                case CollidableType::DOOR:
                    handleDoorCollision();
                    break;
                case CollidableType::SIGN:
                    handleSignCollision();
                    break;
                default:
                    printf("colliding with an invalid collidable\n");
                    break;
            }
//        }
    }
}

void Level::handleNoTypeCollision() {
    printf("colliding with a no type\n");
};
void Level::handleDoorCollision() {
    printf("colliding with a door\n");
};
void Level::handleSignCollision() {
    printf("colliding with a sign\n");
};