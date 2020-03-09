#ifndef NEWNEW_OVERWORLDSCENE_H
#define NEWNEW_OVERWORLDSCENE_H


#include "Scene.h"
#include "../npc/NpcManager.h"
#include "../collisions/CollisionManager.h"
#include "ViewManager.h"
#include "../ui/manager/OverworldUIManager.h"

class OverworldScene : public Scene {

public:
    virtual void initialize(
            std::shared_ptr<EventBus> eventBus,
            std::string sceneName,
            std::string previousSceneName,
            TextureManager& textureManager,
            sf::Font* font,
            sf::Vector2u windowSize,
            sf::Vector2f defaultWindowSize) override;
    virtual void update(sf::Time elapsedTime, bool isPaused, sf::RenderTexture& renderTexture, sf::View& view) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void release(TextureManager& textureManager) override;
    void openDialogue(std::string dialogueTextAssetName) override;
    void closeDialogue() override;
    void handleControllerMenuButtonPressed() override;
    void handleControllerActionButtonPressed() override;
    void handleControllerCancelButtonPressed() override;
    void handleControllerMenuMoveButtonPressed(MoveDirection direction) override;

    sf::Vector2u getMapTileSize();
    std::vector<std::shared_ptr<Collidable>>& getMapCollidables();
    std::vector<Collidable> getNpcCollidables();
    std::map<std::string, sf::IntRect> getNpcMoveBoundariesMap();
    std::map<std::string, std::vector<tmx::Property>> getNpcNameToPropertiesMap();
    Collidable getPlayerCollidable(std::string spawnName);
    std::string getPlayerSpawnNameForPreviousToCurrentSceneTransition(std::string sceneName);

private:
    std::vector<sf::VertexArray> vertices;
    std::shared_ptr<Player> player;
    SceneMap sceneMap;
    MapLoader mapLoader;
    NpcManager npcManager;
    CollisionManager collisionManager;
    OverworldUIManager uiManager;
};


#endif //NEWNEW_OVERWORLDSCENE_H
