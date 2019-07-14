#include "../../includes/text/TextManager.h"

Logger TextManager::logger("TextManager");

TextManager::TextManager() : defaultDialogueEvent("default") { }

void TextManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, sf::Font* font) {
    this->eventBus = eventBus;

    this->dialogueBoxSprite.setTexture(*texture);
    this->dialogueBoxSprite.scale(0.33f, 0.33f); //TODO: this shouldn't be done this way. Dialog box should just be drawn at the right size for the view
    this->dialogueText.setFillColor(sf::Color::Black);
    this->dialogueText.setLineSpacing(1.2f);
    this->dialogueText.setFont(*font);
    this->dialogueText.setCharacterSize(64);

    eventBus->subscribe(this, &TextManager::onControllerActionEvent);
    eventBus->subscribe(this, &TextManager::onOpenDialogueEvent);

    Dialogue defaultDialogue("Nothing to see here.", "");
    defaultDialogueEvent.addDialogue(defaultDialogue);
}

void TextManager::update(sf::RenderWindow* window, sf::View& view, sf::Time deltaTime) {
    if(dialogueIsActive) {
        if(!dialoguePositionSet) {
            setPositionsOnDialogueIsActive(window, view);
        }

        updateText(deltaTime);
    }
}

void TextManager::drawToRenderTexture(sf::RenderTexture* renderTexture) {
    if(dialogueIsActive) {
        renderTexture->draw(dialogueBoxSprite);
    }
}

void TextManager::drawToRenderTextureForDefaultView(sf::RenderTexture* renderTexture) {
    if(dialogueIsActive) {
        renderTexture->draw(dialogueText);
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
    coordsToPixel.y = coordsToPixel.y + (dialogueBoxSprite.getTextureRect().height / 3); //TODO: why the magic numbers
    dialogueText.setPosition(coordsToPixel.x, coordsToPixel.y);
}

void TextManager::onOpenDialogueEvent(OpenDialogueEvent* event) {
    logger.logDebug("ready to handle the dialogue box in TextManager");
    entityPlayerInteractedWith = event->interactedWith;
    initializeText();
    dialogueIsActive = true;
}

void TextManager::closeDialogue() {
    dialogueIsActive = false;
    dialoguePositionSet = false;
    this->stringBeingDrawn = "";
    this->dialogueText.setString("");
    this->currentDialogueEvent.reset();
    eventBus->publish(new CloseDialogueEvent(entityPlayerInteractedWith));
}

void TextManager::onControllerActionEvent(ControllerActionEvent* event) {
    if(dialogueIsActive) {

        if(currentDialogueEvent->shouldStartNextDialogue()) {
            startNextDialogue();
        } else if(!currentDialogueEvent->currentDialogueDone()) {
            //player wants to rush the dialogue by mashing action button
            rushDrawText();
        } else if(currentDialogueEvent->isDialogueEventDone()) {
            closeDialogue();
        }
    }
}

void TextManager::initializeText() {
    std::string entityName = entityPlayerInteractedWith.getName();

    currentDialogueEvent = nullptr;
    for(int i = 0; i < entityDialogueEvents.size(); i++) {
        if(entityDialogueEvents[i].getName() == entityName) {
            currentDialogueEvent = std::make_unique<DialogueEvent>(entityDialogueEvents[i]);
            break;
        }
    }

    if(currentDialogueEvent == nullptr) {
        currentDialogueEvent = std::make_unique<DialogueEvent>(defaultDialogueEvent);
    }

    currentDialogueEvent->startNextDialogue();
    this->stringBeingDrawn = "";
}

void TextManager::updateText(sf::Time deltaTime) {
    if(!currentDialogueEvent->currentDialogueDone()) {
        stringDrawTimer += deltaTime;
        if(stringDrawTimer.asMilliseconds() > 20) {
            drawMoreText();
        }
    }

}

void TextManager::drawMoreText() {
    std::string& dialoguePiece = currentDialogueEvent->getCurrentDialoguePiece();

    this->stringBeingDrawn += dialoguePiece[0];
    this->dialogueText.setString(stringBeingDrawn);

    dialoguePiece = dialoguePiece.erase(0, 1); //changing the reference to currentDialoguePiece
    stringDrawTimer = stringDrawTimer.Zero;
}

void TextManager::rushDrawText() {
    std::string& dialoguePiece = currentDialogueEvent->getCurrentDialoguePiece();

    this->stringBeingDrawn += dialoguePiece;
    this->dialogueText.setString(stringBeingDrawn);

    dialoguePiece = dialoguePiece.erase(0, dialoguePiece.length()); //changing the reference to currentDialoguePiece
    stringDrawTimer = stringDrawTimer.Zero;
}

void TextManager::startNextDialogue() {
    this->stringBeingDrawn = "";
    currentDialogueEvent->startNextDialogue();
}

void TextManager::setEntityDialogueEvents(std::vector<DialogueEvent> entityDialogueEvents) {
    this->entityDialogueEvents = entityDialogueEvents;
}