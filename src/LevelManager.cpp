#include "../includes/LevelManager.h"

void LevelManager::initialize(sf::Texture* playerTexture, sf::Vector2u windowSize) {
    level.initialize(AssetPath::LEVEL_TILEMAP); //TODO: this should be passed to LevelManager or at least decided else where
    viewManager.initializeViewForLevel(level.getMapSizeInPixels(), windowSize);
    player.initialize(playerTexture, level.getMapSizeInPixels().x, level.getMapSizeInPixels().y);
}

void LevelManager::update(sf::Time elapsedTime) {
    viewManager.update(elapsedTime);
    level.handleCollisions();
    player.update(elapsedTime, viewManager.getViewPosition());
}

void LevelManager::draw(sf::RenderWindow* window) {
    window->setView(viewManager.getView());
    window->draw(level);
    window->draw(player);
}

void LevelManager::handleMoveUp() {
    player.moveUp();
    viewManager.moveUp();
}

void LevelManager::handleMoveLeft() {
    player.moveLeft();
    viewManager.moveLeft();
}

void LevelManager::handleMoveDown() {
    player.moveDown();
    viewManager.moveDown();
}

void LevelManager::handleMoveRight() {
    player.moveRight();
    viewManager.moveRight();
}

void LevelManager::handleMoveStop() {
    player.stop();
    viewManager.stop();
}