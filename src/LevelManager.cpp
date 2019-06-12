#include "../includes/LevelManager.h"

void LevelManager::initialize(sf::Texture* playerTexture, sf::Vector2u windowSize) {
    level.initialize(AssetPath::LEVEL_TILEMAP); //TODO: this should be passed to LevelManager or at least decided else where
    viewManager.initializeViewForLevel(level.getMapSizeInPixels());
    player.initialize(playerTexture, level.getMapSizeInPixels().x, level.getMapSizeInPixels().y);
}

void LevelManager::update(sf::Time elapsedTime) {
    viewManager.update(elapsedTime);
    player.update(elapsedTime, viewManager.getViewPosition());
    handleCollisions();
}

void LevelManager::draw(sf::RenderWindow* window) {
    window->setView(viewManager.getView());
    window->draw(level);
    window->draw(player);
}

void LevelManager::handleCollisions() {
    std::vector<Collidable> collisions = level.handleCollisions(player.getGlobalBounds());

    //TODO: eventually need to consider that these collisions will happen to more than just a player
    for(Collidable collidable : collisions) {
        switch (collidable.getType()) {
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
    }
}

void LevelManager::handleNoTypeCollision() {
    printf("colliding with a no type\n");
    handlePlayerCollision();
}

void LevelManager::handleDoorCollision() {
    printf("colliding with a door\n");
}

void LevelManager::handleSignCollision() {
    printf("colliding with a sign\n");
    handlePlayerCollision();
}

void LevelManager::handlePlayerCollision() {
    viewManager.undoMovement();
    player.updatePlayerPosition(viewManager.getViewPosition());
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