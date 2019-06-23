#include "../../includes/text/TextManager.h"

void TextManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, sf::Font* font) {
    this->eventBus = eventBus;

    this->dialogueBoxSprite.setTexture(*texture);
    this->dialogueBoxSprite.scale(0.33f, 0.33f); //TODO: this shouldn't be done this way. Dialog box should just be drawn at the right size for the view
    this->dialogueText.setString("Nothing to see here."); //TODO: delete this
    this->dialogueText.setFillColor(sf::Color::Black);
    this->dialogueText.setLineSpacing(1.1f);
    this->dialogueText.setFont(*font);
    this->dialogueText.setCharacterSize(60);

    eventBus->subscribe(this, &TextManager::onControllerActionEvent);
    eventBus->subscribe(this, &TextManager::onOpenDialogueEvent);
}

void TextManager::update(sf::RenderWindow* window, sf::View& view) {
    if(dialogueIsActive) {
        if(!dialoguePositionSet) {
            setPositionsOnDialogueIsActive(window, view);
        }

        // updateTextReadyToDraw();
    }
}

void TextManager::draw(sf::RenderWindow* window) {
    if(dialogueIsActive) {
        window->draw(dialogueBoxSprite);
    }
}

void TextManager::drawForDefaultView(sf::RenderWindow* window) {
    if(dialogueIsActive) {
        window->draw(dialogueText);
    }
}

void TextManager::setPositionsOnDialogueIsActive(sf::RenderWindow* window, sf::View& view) {
    updateDialogueBoxPosition(view);
    updateDialogueTextPosition(window, view);
    dialoguePositionSet = true;
}

void TextManager::updateDialogueBoxPosition(sf::View& view) {
    sf::Vector2f centerOfView = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    float dialogueBoxX = centerOfView.x - (viewSize.x / 2) + (viewSize.x - dialogueBoxSprite.getGlobalBounds().width)/2;
    float dialogueBoxY = centerOfView.y + (viewSize.y / 2) - dialogueBoxSprite.getGlobalBounds().height;
    dialogueBoxSprite.setPosition(dialogueBoxX, dialogueBoxY);
}

void TextManager::updateDialogueTextPosition(sf::RenderWindow* window, sf::View& view) {
    sf::Vector2i coordsToPixel = window->mapCoordsToPixel(dialogueBoxSprite.getPosition(), view);
    coordsToPixel.x = coordsToPixel.x + (dialogueBoxSprite.getTextureRect().width / 14); //NOTE: using textureRect with because text is drawn to default view instead of camera view
    coordsToPixel.y = coordsToPixel.y + (dialogueBoxSprite.getTextureRect().height / 3);
    dialogueText.setPosition(coordsToPixel.x, coordsToPixel.y);
}

void TextManager::closeDialogue() {
    dialogueIsActive = false;
    dialoguePositionSet = false;
    eventBus->publish(new CloseDialogueEvent());
}

void TextManager::onControllerActionEvent(ControllerActionEvent* event) {
    if(dialogueIsActive) {
        closeDialogue();
    }
}

void TextManager::onOpenDialogueEvent(OpenDialogueEvent* event) {
    printf("ready to handle the dialogue box in TextManager\n");
//    const Collidable& collidable = event->interactedWith; //TODO: will be used to decide what dialogue to display

//    this->stringToDraw = "Nothing to see here.";
//    this->stringReadyToDraw = stringToDraw[0];
//    this->stringToDraw = stringToDraw.erase(0, 1);
//    this->dialogueText.setString(stringReadyToDraw);

    dialogueIsActive = true;
}