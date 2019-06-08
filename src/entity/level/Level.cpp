#include "../../../includes/entity/level/Level.h"

const float LEVEL_MOVEMENT_SPEED = 270.f;
//TODO: should an AnimatedEntity and Level both derive from a BaseEntity? Basically Entity without the animation stuff. Will help with scaling too
//TODO: at the very least, need a higher level place to set the scale and pass to Entitys and levels

Level::Level(float windowWidth, float windowHeight, std::string tileMapPath) : TileMap(tileMapPath), movement(0.f, 0.f) {

    this->speed = LEVEL_MOVEMENT_SPEED;
    this->scale(sf::Vector2f(5.f, 5.f));

    view.setCenter(sf::Vector2f(windowWidth / 2, windowHeight / 2));
    view.setSize(sf::Vector2f(windowWidth, windowHeight));
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &texture;

    for(sf::VertexArray vertexArray : vertices) {
        target.draw(vertexArray, states);
    }
}

sf::View Level::getView() const {
    return this->view;
}

void Level::update(sf::Time deltaTime) {
    this->move(movement * deltaTime.asSeconds());

    //NOTE: rounding the position gets rid of weird artifacting/flickering that was introduced after tile maps. any negative repercussions?
    this->setPosition(std::round(this->getPosition().x), std::round(this->getPosition().y));
}

void Level::moveUp() {
    resetMovement();
    movement.y += speed;
}

void Level::moveLeft() {
    resetMovement();
    movement.x += speed;
}

void Level::moveDown() {
    resetMovement();
    movement.y -= speed;
}

void Level::moveRight() {
    resetMovement();
    movement.x -= speed;
}

void Level::stop() {
    resetMovement();
}

void Level::resetMovement() {
    movement.x = 0;
    movement.y = 0;
}