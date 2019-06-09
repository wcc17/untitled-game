#include "../../../includes/entity/level/Level.h"

const float LEVEL_MOVEMENT_SPEED = 120.f;

Level::Level(float windowWidth, float windowHeight, std::string tileMapPath) : TileMap(tileMapPath), movement(0.f, 0.f) {
    this->speed = LEVEL_MOVEMENT_SPEED;

    //TODO: view stuff should be handled somewhere else, not in Level
    view.setCenter(sf::Vector2f(mapSizeInPixels.x / 2, mapSizeInPixels.y / 2));
    view.setSize(sf::Vector2f(windowWidth / 5, windowHeight / 5));
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &texture;

    for(sf::VertexArray vertexArray : vertices) {
        target.draw(vertexArray, states);
    }
}

void Level::update(sf::Time deltaTime) {
//    printf("position: %f, %f \n", view.getCenter().x, view.getCenter().y);
    view.move(movement * deltaTime.asSeconds());

    //NOTE: rounding the position gets rid of weird artifacting/flickering that was introduced after tile maps. any negative repercussions?
    //NOTE: setting the position AFTER checking collisions, or else that will mess with the float precision collision detecting (i think)
    view.setCenter(std::round(view.getCenter().x), std::round(view.getCenter().y));
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

void Level::moveUp() {
    resetMovement();
    movement.y -= speed;
}

void Level::moveLeft() {
    resetMovement();
    movement.x -= speed;
}

void Level::moveDown() {
    resetMovement();
    movement.y += speed;
}

void Level::moveRight() {
    resetMovement();
    movement.x += speed;
}

void Level::stop() {
    resetMovement();
}

void Level::resetMovement() {
    movement.x = 0;
    movement.y = 0;
}

sf::View Level::getView() const {
    return this->view;
}

sf::Vector2f Level::getViewPosition() {
    return this->view.getCenter();
}