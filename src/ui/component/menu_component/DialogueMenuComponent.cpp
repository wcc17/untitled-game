#include "../../../../includes/ui/component/menu_component/DialogueMenuComponent.h"

void DialogueMenuComponent::initialize(
        sf::Font *font,
        float windowScale,
        sf::Texture *componentTexture,
        ScreenPosition screenPosition,
        UIComponentType componentType) {
    BaseMenuComponent::initialize(
            font,
            windowScale,
            componentTexture,
            screenPosition,
            componentType);
    dialogueManager.initialize();
}

void DialogueMenuComponent::update(
        sf::RenderTexture& renderTexture,
        sf::View& view,
        sf::Time deltaTime) {
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

void DialogueMenuComponent::handleControllerActionButtonPressed() {
    dialogueManager.handleControllerActionButtonPressed();
}

void DialogueMenuComponent::openDialogueWithSubstitutions(
        std::string nameOfDialogueTextAsset,
        std::vector<std::string> textSubstitutions) {
    dialogueManager.openDialogueWithSubstitutions(nameOfDialogueTextAsset, textSubstitutions);
}

void DialogueMenuComponent::openDialogue(std::string nameOfDialogueTextAsset) {
    dialogueManager.openDialogue(nameOfDialogueTextAsset);
}

bool DialogueMenuComponent::componentActionIsFinished() {
    return dialogueManager.isDialogueEventDone();
}
