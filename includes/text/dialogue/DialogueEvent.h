#ifndef NEWNEW_DIALOGUEEVENT_H
#define NEWNEW_DIALOGUEEVENT_H


#include <vector>
#include "Dialogue.h"

class DialogueEvent {
public:
    DialogueEvent(std::vector<Dialogue> dialogues);
    std::string& getCurrentDialoguePiece();
    void startNextDialogue();
    bool dialoguesLeftToDraw();
    bool shouldStartNextDialogue();
    bool currentDialogueDone();
    bool isDialogueEventDone();
private:
    std::unique_ptr<Dialogue> currentDialogue;
    std::vector<Dialogue> dialogues;
};


#endif //NEWNEW_DIALOGUEEVENT_H
