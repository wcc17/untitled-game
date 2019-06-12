#include "../../includes/manager/LevelManager.h"

void LevelManager::initialize() {
    level.initialize(AssetPath::LEVEL_TILEMAP); //TODO: this should be decided else where when switching level logic is implemented. Probably in a GameManager one level up
    viewManager.initializeViewForLevel(level.getMapSizeInPixels());

    textureManager.loadTexture(AssetPath::PLAYER_TEXTURE);
    player.initialize(textureManager.getTexture(AssetPath::PLAYER_TEXTURE), level.getMapSizeInPixels().x, level.getMapSizeInPixels().y);
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
    //TODO: eventually need to consider that these collisions will happen to more than just a player
    std::vector<Collidable> collisions = level.handleCollisions(player.getGlobalBounds());
    for(Collidable collidable : collisions) {
        switch (collidable.getType()) {
            case CollidableType::WALL:
                handleWallCollision();
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

void LevelManager::handleWallCollision() {
    // printf("colliding with a wall\n");
    handlePlayerCollision();
}

void LevelManager::handleDoorCollision() {
    // printf("colliding with a door\n");
}

void LevelManager::handleSignCollision() {
    // printf("colliding with a sign\n");
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

void LevelManager::release() {
    textureManager.releaseTextures();
}