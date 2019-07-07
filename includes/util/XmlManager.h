#ifndef NEWNEW_XMLMANAGER_H
#define NEWNEW_XMLMANAGER_H

#include <tinyxml2.h>
#include "Logger.h"
#include "../text/dialogue/DialogueEvent.h"

class XmlManager {
public:
    std::vector<DialogueEvent> loadEntityDialogueForScene(std::string sceneName);
private:
    static Logger logger;
    static DialogueEvent loadEntityDialogueEvent(tinyxml2::XMLElement* entityDialogueEventElement);
    static Dialogue loadEntityDialogue(tinyxml2::XMLElement* entityDialoguePieceElement);
    static std::string getTextFromElement(tinyxml2::XMLElement* element);
};


#endif //NEWNEW_XMLMANAGER_H
