#ifndef NEWNEW_DIALOGUEMANAGER_H
#define NEWNEW_DIALOGUEMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "../../events/event/ControllerActionEvent.h"
#include "../../events/event/CloseDialogueEvent.h"
#include "../../events/event/OpenDialogueEvent.h"
#include "../../events/EventBus.h"
#include "../../events/EventBus.h"
#include "DialogueEvent.h"
#include "../../util/Logger.h"
#include "../../asset/TextureManager.h"
#include "../../asset/AssetPath.h"
#include "PrintableDialogueText.h"

class DialogueManager {
public:
    DialogueManager();
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, sf::Font* font, float windowScale);
    void update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime);
    void drawToRenderTexture(sf::RenderTexture* renderTexture);
    void setEntityDialogueEvents(std::vector<DialogueEvent> entityDialogueEvents);
    void onControllerActionEvent();
    void onOpenDialogueEvent(OpenDialogueEvent* event);
    bool isDialogueActive();
    void release(TextureManager& textureManager);

private:
    enum DialogueState {
        STATE_READY,
        STATE_ACTIVE,
        STATE_INACTIVE
    };

    DialogueState dialogueState = STATE_INACTIVE;

    std::shared_ptr<EventBus> eventBus;
    std::vector<DialogueEvent> entityDialogueEvents;
    DialogueEvent defaultDialogueEvent;
    PrintableDialogueText printableDialogueText;
    sf::Sprite dialogueBoxSprite;
    Collidable entityPlayerInteractedWith;
    float windowScale;

    static Logger logger;

    void closeDialogue();
    void setPositionsOnDialogueIsActive(sf::RenderTexture& renderTexture, sf::View& view);
    void updateDialogueBoxPosition(const sf::Vector2f& viewCenter, const sf::Vector2f& viewSize);
    void updateDialogueTextPosition(sf::RenderTexture& renderTexture, sf::View& view);
    DialogueEvent getDialogueEventForEntityWithName(std::string entityName);
};


#endif //NEWNEW_DIALOGUEMANAGER_H
