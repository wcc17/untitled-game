#ifndef NEWNEW_OVERWORLDSCENE_H
#define NEWNEW_OVERWORLDSCENE_H


#include "Scene.h"

class OverworldScene : public Scene {

public:
    virtual void initialize(std::string sceneName, TextureManager& textureManager) override;
    virtual void update() override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void release(TextureManager& textureManager) override;

    sf::Vector2u getMapTileSize();
    std::vector<std::shared_ptr<Collidable>>& getMapCollidables();
    std::vector<Collidable> getNpcCollidables();
    std::map<std::string, sf::IntRect> getNpcMoveBoundariesMap();
    std::map<std::string, std::vector<tmx::Property>> getNpcNameToPropertiesMap();
    Collidable getPlayerCollidable(std::string spawnName);
    std::string getPlayerSpawnNameForPreviousToCurrentSceneTransition(std::string sceneName);

private:
    std::vector<sf::VertexArray> vertices;
    SceneMap sceneMap;
    MapLoader mapLoader;

};


#endif //NEWNEW_OVERWORLDSCENE_H
