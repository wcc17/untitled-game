#include "../../includes/util/XmlManager.h"
#include "../../includes/text/dialogue/DialogueEvent.h"

Logger XmlManager::logger("XmlManager");

std::vector<DialogueEvent> XmlManager::loadEntityDialogueForScene(std::string sceneName) {
    std::string filePath = "assets/xml/dialogue/scene/" + sceneName + ".xml"; //TODO: needs a method in AssetPath

    tinyxml2::XMLDocument doc;
    std::vector<DialogueEvent> dialogueEvents;
    doc.LoadFile(filePath.c_str());

    if(!doc.Error()) {
        tinyxml2::XMLElement* entityElement = doc.FirstChildElement("entity");
        tinyxml2::XMLElement* entityDialogueEventElement = entityElement->FirstChildElement();
        while(entityDialogueEventElement) {
            DialogueEvent event = loadEntityDialogueEvent(entityDialogueEventElement);
            dialogueEvents.push_back(event);

            entityDialogueEventElement = entityDialogueEventElement->NextSiblingElement();
        }
    }

    return dialogueEvents;
}

DialogueEvent XmlManager::loadEntityDialogueEvent(tinyxml2::XMLElement* entityDialogueEventElement) {
    std::string entityName = entityDialogueEventElement->Attribute("name");
    DialogueEvent dialogueEvent(entityName);

    tinyxml2::XMLElement* entityDialogueElement = entityDialogueEventElement->FirstChildElement();
    while(entityDialogueElement) {
        tinyxml2::XMLElement* entityDialoguePieceElement = entityDialogueElement->FirstChildElement();
        Dialogue dialogue = loadEntityDialogue(entityDialoguePieceElement);
        dialogueEvent.addDialogue(dialogue);

        entityDialogueElement = entityDialogueElement->NextSiblingElement();
    }

    return dialogueEvent;
}

Dialogue XmlManager::loadEntityDialogue(tinyxml2::XMLElement* entityDialoguePieceElement) {
    std::string firstPiece = getTextFromElement(entityDialoguePieceElement);
    std::string secondPiece = "";

    if(entityDialoguePieceElement->NextSiblingElement()) {
        entityDialoguePieceElement = entityDialoguePieceElement->NextSiblingElement();
        secondPiece = getTextFromElement(entityDialoguePieceElement);
    }

    Dialogue dialogue(firstPiece, secondPiece);
    return dialogue;
}

std::string XmlManager::getTextFromElement(tinyxml2::XMLElement* element) {
    return element->FirstChild()->ToText()->Value();
}
