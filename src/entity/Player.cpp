#include "../../includes/entity/Player.h"

Player::Player(sf::Texture* texture, int windowWidth, int windowHeight) : Entity(texture) {
    //TODO: if window is resized, we will need to update the player's position. the player is always in the middle of the screen
    this->setPosition(windowWidth / 2 - this->getGlobalBounds().width / 2, windowHeight / 2 - this->getGlobalBounds().height / 2);
}

