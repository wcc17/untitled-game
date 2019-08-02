#include "../../../includes/ui/dialogue/PrintableDialogueText.h"

void PrintableDialogueText::initialize(sf::Font* font, float windowScale) {
    this->setFillColor(sf::Color::Black);
    this->setLineSpacing(1.2f);
    this->setFont(*font);
    this->setCharacterSize(64 * windowScale);
}

void PrintableDialogueText::update(sf::Time deltaTime) {
    if(!currentDialogueEvent->currentDialogueDone()) {
        stringDrawTimer += deltaTime;
        if(stringDrawTimer.asMilliseconds() > 20) {
            printMoreText();
        }
    }
}

void PrintableDialogueText::startNewDialogueEvent(DialogueEvent dialogueEvent) {
    currentDialogueEvent.reset();
    currentDialogueEvent = std::make_unique<DialogueEvent>(dialogueEvent);

    currentDialogueEvent->startNextDialogue();
    this->stringBeingDrawn = "";
}

void PrintableDialogueText::onControllerEvent() {
    if(currentDialogueEvent->shouldStartNextDialogue()) {
        startNextDialogue();
    } else if(!currentDialogueEvent->currentDialogueDone()) {
        //player wants to rush the dialogue by mashing action button
        rushPrintText();
    }
}

bool PrintableDialogueText::isDialogueFinishedPrinting() {
    return currentDialogueEvent->isDialogueEventDone();
}

void PrintableDialogueText::reset() {
    this->stringBeingDrawn = "";
    this->setString("");
    this->currentDialogueEvent.reset();
}

void PrintableDialogueText::printMoreText() {
    std::string& dialoguePiece = currentDialogueEvent->getCurrentDialoguePiece();

    this->stringBeingDrawn += dialoguePiece[0];
    this->setString(stringBeingDrawn);

    dialoguePiece = dialoguePiece.erase(0, 1); //changing the reference to currentDialoguePiece
    stringDrawTimer = stringDrawTimer.Zero;
}

void PrintableDialogueText::startNextDialogue() {
    this->stringBeingDrawn = "";
    currentDialogueEvent->startNextDialogue();
}

void PrintableDialogueText::rushPrintText() {
    std::string& dialoguePiece = currentDialogueEvent->getCurrentDialoguePiece();

    this->stringBeingDrawn += dialoguePiece;
    this->setString(stringBeingDrawn);

    dialoguePiece = dialoguePiece.erase(0, dialoguePiece.length()); //changing the reference to currentDialoguePiece
    stringDrawTimer = stringDrawTimer.Zero;
}