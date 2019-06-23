#include "../../includes/text/TextManager.h"

void TextManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, sf::Font* font) {
    this->eventBus = eventBus;

    this->dialogueBoxSprite.setTexture(*texture);
    this->dialogueBoxSprite.scale(0.33f, 0.33f); //TODO: this shouldn't be done this way. Dialog box should just be drawn at the right size for the view
    this->dialogueText.setFillColor(sf::Color::Black);
    this->dialogueText.setString("Nothing to see here.");
    this->dialogueText.setFont(*font);
    this->dialogueText.setCharacterSize(46);

    eventBus->subscribe(this, &TextManager::onControllerActionEvent);
    eventBus->subscribe(this, &TextManager::onOpenDialogueEvent);
}

void TextManager::update() {

}

void TextManager::draw(sf::RenderWindow* window) {
    if(showDialogueBox) {
        window->draw(dialogueBoxSprite);
    }
}

void TextManager::drawForDefaultView(sf::RenderWindow* window) {
    if(showDialogueBox) {
        window->draw(dialogueText);
    }
}

void TextManager::onControllerActionEvent(ControllerActionEvent* event) {
    if(showDialogueBox) {
        showDialogueBox = false;
        eventBus->publish(new CloseDialogueEvent());
    }
}

void TextManager::onOpenDialogueEvent(OpenDialogueEvent* event) {
//    printf("ready to handle the dialogue box in TextManager\n");
//    const Collidable& collidable = event->interactedWith;
//
////    sf::Vector2f centerOfView = sf::Vector2f(playerBounds.left + (playerBounds.width / 2), playerBounds.top + (playerBounds.height / 2));
//    sf::Vector2f centerOfView = view->getCenter();
//    float dialogueBoxX = centerOfView.x - (viewSize.x / 2) + (viewSize.x - dialogueBoxSprite.getGlobalBounds().width)/2;
//    float dialogueBoxY = centerOfView.y + (viewSize.y / 2) - dialogueBoxSprite.getGlobalBounds().height;
//    dialogueBoxSprite.setPosition(dialogueBoxX, dialogueBoxY);
//
//    sf::Vector2f pixelToCoords = window->mapPixelToCoords(sf::Vector2i(dialogueBoxSprite.getPosition().x, dialogueBoxSprite.getPosition().y), *view);
//    sf::Vector2i coordsToPixel = window->mapCoordsToPixel(dialogueBoxSprite.getPosition(), *view);
//
//    dialogueText.setPosition(coordsToPixel.x, coordsToPixel.y);

    showDialogueBox = true;
}