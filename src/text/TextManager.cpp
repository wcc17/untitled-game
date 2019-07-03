#include "../../includes/text/TextManager.h"

void TextManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, sf::Font* font) {
    this->eventBus = eventBus;

    this->dialogueBoxSprite.setTexture(*texture);
    this->dialogueBoxSprite.scale(0.33f, 0.33f); //TODO: this shouldn't be done this way. Dialog box should just be drawn at the right size for the view
    this->dialogueText.setFillColor(sf::Color::Black);
    this->dialogueText.setLineSpacing(1.1f);
    this->dialogueText.setFont(*font);
    this->dialogueText.setCharacterSize(60);

    eventBus->subscribe(this, &TextManager::onControllerActionEvent);
    eventBus->subscribe(this, &TextManager::onOpenDialogueEvent);
}

void TextManager::update(sf::RenderWindow* window, sf::View& view, sf::Time deltaTime) {
    if(dialogueIsActive) {
        if(!dialoguePositionSet) {
            setPositionsOnDialogueIsActive(window, view);
        }

        updateText(deltaTime);
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

//TODO: I think the dialogue stuff should be in its own class. See C++ composition maybe?
void TextManager::onOpenDialogueEvent(OpenDialogueEvent* event) {
    printf("ready to handle the dialogue box in TextManager\n");
    entityPlayerInteractedWith = event->interactedWith;

    /**
     * Just an example, not final
     *
     * <dialogueEvent>
     *   <dialogue>
     *    <dialoguePiece>Hello, this is some text!</dialoguePiece>
     *    <dialoguePiece>This is just a test though... It can be as long as I want, but if its too long, it'll be split into seperate lines</dialoguePiece>
     *   </dialogue>
     *
     *   <dialogue>
     *    <dialoguePiece>I want this to be the only text to appear in the box!</dialoguePiece>
     *   </dialogue>
     * </dialogueEvent>
     * Opens up future where I can give certain dialoguePieces special effects, change their font size, etc.
     */

    initializeText();
    dialogueIsActive = true;
}

void TextManager::closeDialogue() {
    dialogueIsActive = false;
    dialoguePositionSet = false;
    this->stringBeingDrawn = "";
    this->dialogueText.setString("");
    eventBus->publish(new CloseDialogueEvent(entityPlayerInteractedWith));
}

void TextManager::onControllerActionEvent(ControllerActionEvent* event) {
    if(dialogueIsActive) {

        if(dialogueEvent->shouldStartNextDialogue()) {
            startNextDialogue();
        } else if(!dialogueEvent->currentDialogueDone()) {
            //player wants to rush the dialogue by mashing action button
            rushDrawText();
        } else if(dialogueEvent->isDialogueEventDone()) {
            closeDialogue();
        }
    }
}

void TextManager::initializeText() {
    //TODO: manually inserting new line character, but that should happen when loading the first line from file
    //TODO: this should all happen elsewhere when loading dialogue info from a file
    std::vector<Dialogue> dialogues;
    dialogues.push_back(Dialogue("Nothing to see here.\n", "Actually there is SOMETHING to see here"));
    dialogues.push_back(Dialogue("This is the second dialogue piece object.\n", "I'm done talking to you now"));
    dialogueEvent = std::make_unique<DialogueEvent>(dialogues);

    this->stringBeingDrawn = "";
}

void TextManager::updateText(sf::Time deltaTime) {
    if(!dialogueEvent->currentDialogueDone()) {
        stringDrawTimer += deltaTime;
        if(stringDrawTimer.asMilliseconds() > 20) {
            drawMoreText();
        }
    }

}

void TextManager::drawMoreText() {
    std::string& dialoguePiece = dialogueEvent->getCurrentDialoguePiece();

    this->stringBeingDrawn += dialoguePiece[0];
    this->dialogueText.setString(stringBeingDrawn);

    dialoguePiece = dialoguePiece.erase(0, 1); //changing the reference to currentDialoguePiece
    stringDrawTimer = stringDrawTimer.Zero;
}

void TextManager::rushDrawText() {
    std::string& dialoguePiece = dialogueEvent->getCurrentDialoguePiece();

    this->stringBeingDrawn += dialoguePiece;
    this->dialogueText.setString(stringBeingDrawn);

    dialoguePiece = dialoguePiece.erase(0, dialoguePiece.length()); //changing the reference to currentDialoguePiece
    stringDrawTimer = stringDrawTimer.Zero;
}

void TextManager::startNextDialogue() {
    this->stringBeingDrawn = "";
    dialogueEvent->startNextDialogue();
}