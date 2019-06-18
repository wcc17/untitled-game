#include "../../../includes/entity/character/NpcEntity.h"

//TODO: i don't think I want these here, NpcEntity will be able to be different sizes in multiples of 8
const float ENTITY_WIDTH = 16.f;
const float ENTITY_HEIGHT = 24.f;

void NpcEntity::initialize(sf::Texture* texture, std::string npcName, CollidableType collidableType, sf::FloatRect bounds) {
    AnimatedEntity::initialize(texture);
    name = npcName;
    type = collidableType;

    boundingBox.left = bounds.left;
    boundingBox.top = bounds.top;
    boundingBox.width = ENTITY_WIDTH; 
    boundingBox.height = ENTITY_HEIGHT; 

    setPosition(sf::Vector2f(boundingBox.left, boundingBox.top));
    setFrameTime(sf::seconds(0.16f)); //TODO: not sure where I want to load this from yet

    initializeAnimations();
}

void NpcEntity::update(sf::Time deltaTime) {
    updateBoundingBox(this->getGlobalBounds());
    AnimatedEntity::update(deltaTime);
}

//TODO: this is the exact same as Player. I think this won't always be the same for specific types of Entities. Leaving for now
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
    updateBoundingBox(this->getGlobalBounds());
}