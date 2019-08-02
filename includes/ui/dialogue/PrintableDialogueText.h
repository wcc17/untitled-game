#ifndef NEWNEW_PRINTABLEDIALOGUETEXT_H
#define NEWNEW_PRINTABLEDIALOGUETEXT_H


#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include "DialogueEvent.h"

class PrintableDialogueText : public sf::Text {

public:
    void initialize(sf::Font* font, float windowScale);
    void update(sf::Time deltaTime);
    void startNewDialogueEvent(DialogueEvent dialogueEvent);
    void onControllerEvent();
    bool isDialogueFinishedPrinting();
    void reset();

private:
    std::string stringBeingDrawn;
    sf::Time stringDrawTimer;
    std::unique_ptr<DialogueEvent> currentDialogueEvent;

    void printMoreText();
    void startNextDialogue();
    void rushPrintText();
};


#endif //NEWNEW_PRINTABLEDIALOGUETEXT_H
