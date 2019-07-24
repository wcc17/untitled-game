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
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, sf::Font* font, float windowScale);
    void update(sf::RenderWindow* window, sf::View& view, sf::Time deltaTime);
    void drawToRenderTexture(sf::RenderTexture* renderTexture);
    void setEntityDialogueEvents(std::vector<DialogueEvent> entityDialogueEvents);
    void onControllerActionEvent();
    void onOpenDialogueEvent(OpenDialogueEvent* event);
    bool isDialogueActive();
    void release(TextureManager& textureManager);

private:
    std::shared_ptr<EventBus> eventBus;
    sf::Sprite dialogueBoxSprite;
    sf::Text dialogueText;
    std::string stringBeingDrawn;
    sf::Time stringDrawTimer;
    bool dialoguePositionSet = false;
    bool dialogueIsActive = false;
    Collidable entityPlayerInteractedWith;
    float windowScale; //TODO: better name? If default window size is 1920x1080 and actual is 960x540, then scale should be .5f

    static Logger logger;

    std::unique_ptr<DialogueEvent> currentDialogueEvent;
    std::vector<DialogueEvent> entityDialogueEvents;
    DialogueEvent defaultDialogueEvent;

    void closeDialogue();
    void setPositionsOnDialogueIsActive(sf::RenderWindow* window, sf::View& view);
    void updateDialogueBoxPosition(const sf::Vector2f& viewCenter, const sf::Vector2f& viewSize);
    void updateDialogueTextPosition(sf::RenderWindow* window, sf::View& view);
    void initializeText();
    void updateText(sf::Time deltaTime);
    void drawMoreText();
    void rushDrawText();
    void startNextDialogue();
};


#endif //NEWNEW_DIALOGUEMANAGER_H
