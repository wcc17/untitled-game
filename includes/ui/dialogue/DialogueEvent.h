#ifndef NEWNEW_DIALOGUEEVENT_H
#define NEWNEW_DIALOGUEEVENT_H


#include <vector>
#include "Dialogue.h"

class DialogueEvent {
public:
    DialogueEvent(std::string npcName);
    void addDialogue(Dialogue dialogue);
    std::string& getCurrentDialoguePiece();
    void startNextDialogue();
    bool dialoguesLeftToDraw();
    bool shouldStartNextDialogue();
    bool currentDialogueDone();
    bool isDialogueEventDone();
    std::string getName();
    std::vector<Dialogue> getDialogues();
    void setDialogues(std::vector<Dialogue> dialogues);
private:
    Dialogue currentDialogue;
    std::vector<Dialogue> dialogues;
    std::string entityName;
};


#endif //NEWNEW_DIALOGUEEVENT_H
