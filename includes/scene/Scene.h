#ifndef NEWNEW_SCENE_H
#define NEWNEW_SCENE_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cmath>
#include "../map/TileMap.h"
#include "../util/Logger.h"
#include "../asset/TextureManager.h"
#include "../map/SceneMap.h"
#include "../collisions/Collidable.h"
#include "../map/MapLoader.h"

class Scene : public sf::Drawable, public sf::Transformable {
public:
    void initialize(std::string sceneName, TextureManager& textureManager);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void release(TextureManager& textureManager);
    sf::Vector2u getMapTileSize();
    std::string getSceneName();
    std::vector<std::shared_ptr<Collidable>>& getMapCollidables();
    std::vector<Collidable> getNpcCollidables();
    std::map<std::string, sf::IntRect> getNpcMoveBoundariesMap();
    std::map<std::string, std::vector<tmx::Property>> getNpcNameToPropertiesMap();
    Collidable getPlayerCollidable(std::string spawnName);
    std::string getPlayerSpawnPointName(std::string sceneName);

private:
    std::string sceneName;
    sf::Texture* texture;
    std::vector<sf::VertexArray> vertices;
    SceneMap sceneMap;
    MapLoader mapLoader;

    static Logger logger;
};


#endif //NEWNEW_SCENE_H
