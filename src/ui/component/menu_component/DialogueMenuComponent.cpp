#include "../../../../includes/ui/component/menu_component/DialogueMenuComponent.h"

void DialogueMenuComponent::initialize(std::shared_ptr<EventBus> eventBus, sf::Font *font, float windowScale,
                                       sf::Texture *componentTexture, ScreenPosition screenPosition, sf::Vector2f textOffset) {
    BaseMenuComponent::initialize(eventBus, font, windowScale, componentTexture, screenPosition, textOffset);
    dialogueManager.initialize(eventBus);
}

void DialogueMenuComponent::update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime) {
    BaseMenuComponent::update(renderTexture, view, deltaTime);
    dialogueManager.update(renderTexture, view, deltaTime);
    updateTextShownInComponent(dialogueManager.getStringToDraw());
}

void DialogueMenuComponent::updateTextShownInComponent(std::string textToDraw) {
    //TODO: there should only ever be one menu option in DialogueMenuComponent, but error handling should still be here (or at least a log)
    menuOptions[0].setString(textToDraw);
}

void DialogueMenuComponent::setEntityDialogueEvents(std::vector<DialogueEvent> entityDialogueEvents) {
    dialogueManager.setEntityDialogueEvents(entityDialogueEvents);
}

void DialogueMenuComponent::onControllerActionEvent(ControllerActionEvent* event) {
    dialogueManager.onControllerActionEvent();
}

void DialogueMenuComponent::onOpenDialogueEvent(OpenDialogueEvent* event) {
    dialogueManager.onOpenDialogueEvent(event);
}
