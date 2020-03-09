#ifndef NEWNEW_DIALOGUEMANAGER_H
#define NEWNEW_DIALOGUEMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "../../events/event/ControllerActionEvent.h"
#include "../../events/event/CloseDialogueEvent.h"
#include "../../events/event/OpenDialogueEvent.h"
#include "../../events/EventBus.h"
#include <SFML/Graphics/Text.hpp>
#include "../../events/EventBus.h"
#include "DialogueEvent.h"
#include "../../util/Logger.h"
#include "../../asset/TextureManager.h"
#include "../../asset/AssetPath.h"

class DialogueManager {
public:
    DialogueManager();
    void initialize();
    void update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime);
    void setEntityDialogueEvents(std::vector<DialogueEvent> entityDialogueEvents);
    std::string getStringToDraw();
    void handleControllerActionButtonPressed(std::shared_ptr<EventBus> eventBus);
    void openDialogue(std::string nameOfDialogueTextAsset);
    void closeDialogue(std::shared_ptr<EventBus> eventBus);

private:
    enum DialogueState {
        STATE_READY,
        STATE_ACTIVE,
        STATE_INACTIVE
    };

    DialogueState dialogueState = STATE_INACTIVE;

    std::string stringToDraw;
    sf::Time stringDrawTimer;
    std::string nameOfDialogueTextAsset;

    static Logger logger;

    std::unique_ptr<DialogueEvent> currentDialogueEvent;
    std::vector<DialogueEvent> entityDialogueEvents;
    DialogueEvent defaultDialogueEvent;

    void initializeText();
    void updateText(sf::Time deltaTime);
    void drawMoreText();
    void rushDrawText();
    void startNextDialogue();
};


#endif //NEWNEW_DIALOGUEMANAGER_H
