#include "../../includes/level/Level.h"

const float LEVEL_MOVEMENT_SPEED = 270.f;
//TODO: should an AnimatedEntity and Level both derive from a BaseEntity? Basically Entity without the animation stuff. Will help with scaling too
//TODO: at the very least, need a higher level place to set the scale and pass to Entitys and levels

Level::Level(sf::Texture* texture, float windowWidth, float windowHeight) : movement(0.f, 0.f) {
    this->setTexture(*texture);

    this->speed = LEVEL_MOVEMENT_SPEED;
    this->scale(sf::Vector2f(5.f, 5.f));

    view.setCenter(sf::Vector2f(windowWidth / 2, windowHeight / 2));
    view.setSize(sf::Vector2f(windowWidth, windowHeight));
}

sf::View Level::getView() const {
    return this->view;
}

void Level::update(sf::Time deltaTime) {
    this->move(movement * deltaTime.asSeconds());
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
