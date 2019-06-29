#include "../../../includes/entity/character/NpcEntity.h"

//TODO: these will be moved out once there are different entities being loaded
const float ENTITY_WIDTH = 16.f;
const float ENTITY_HEIGHT = 24.f;
const float ENTITY_MOVEMENT_SPEED = 80.f;
const float ENTITY_FRAME_TIME = 0.16f; //TODO: not sure where I want to load this from yet

void NpcEntity::initialize(sf::Texture* texture, const Collidable& collidable) {
    CharacterEntity::initialize(texture, ENTITY_MOVEMENT_SPEED, collidable, ENTITY_FRAME_TIME);
}

void NpcEntity::update(sf::Time deltaTime) {
//    MovableEntity::update(deltaTime);
    AnimatedEntity::update(deltaTime, currentDirection);
    roundPosition();
}

void NpcEntity::turnToFacePlayer(MoveDirection playerFacingDirection) {
    switch(playerFacingDirection) {
        case MoveDirection::UP:
            AnimatedEntity::faceDown();
            break;
        case MoveDirection::DOWN:
            AnimatedEntity::faceUp();
            break;
        case MoveDirection::LEFT:
            AnimatedEntity::faceRight();
            break;
        case MoveDirection::RIGHT:
            AnimatedEntity::faceLeft();
            break;
        case MoveDirection::NONE:
            break;
    }
}

//TODO: EVERYTHING needs to be multiples of  tile size, including the character textures (its frames). There should be a check to ensure this is happening so that I don't forget
void NpcEntity::initializeAnimations() {

    //TODO: these constants are temporary until I figure out where I want to load this information from. Probably from a more specific derived NpcEntity class
    walkingAnimationDown.setSpriteSheet(*this->getTexture());
    walkingAnimationDown.addFrame(sf::IntRect(0, 0, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationDown.addFrame(sf::IntRect(ENTITY_WIDTH, 0, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationDown.addFrame(sf::IntRect(ENTITY_WIDTH*2, 0, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationDown.addFrame(sf::IntRect(ENTITY_WIDTH*3, 0, ENTITY_WIDTH, ENTITY_HEIGHT));

    walkingAnimationRight.setSpriteSheet(*this->getTexture());
    walkingAnimationRight.addFrame(sf::IntRect(0, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationRight.addFrame(sf::IntRect(ENTITY_WIDTH, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationRight.addFrame(sf::IntRect(ENTITY_WIDTH*2, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationRight.addFrame(sf::IntRect(ENTITY_WIDTH*3, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));

    walkingAnimationUp.setSpriteSheet(*this->getTexture());
    walkingAnimationUp.addFrame(sf::IntRect(0, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationUp.addFrame(sf::IntRect(ENTITY_WIDTH, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationUp.addFrame(sf::IntRect(ENTITY_WIDTH*2, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationUp.addFrame(sf::IntRect(ENTITY_WIDTH*3, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));

    walkingAnimationLeft.setSpriteSheet(*this->getTexture());
    walkingAnimationLeft.addFrame(sf::IntRect(0, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationLeft.addFrame(sf::IntRect(ENTITY_WIDTH, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationLeft.addFrame(sf::IntRect(ENTITY_WIDTH*2, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));
    walkingAnimationLeft.addFrame(sf::IntRect(ENTITY_WIDTH*3, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));

    this->currentAnimation = &walkingAnimationDown;
    setTextureRectBasedOnCurrentFrame();
}