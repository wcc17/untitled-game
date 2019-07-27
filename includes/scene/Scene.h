#ifndef NEWNEW_SCENE_H
#define NEWNEW_SCENE_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <tmxlite/Map.hpp>
#include <cmath>
#include "../map/TileMap.h"
#include "../util/Logger.h"
#include "../asset/AssetPath.h"
#include "../asset/TextureManager.h"
#include "../map/SceneObjectMap.h"

class Scene : public sf::Drawable, public sf::Transformable {
public:
    void initialize(std::string sceneName, TextureManager& textureManager);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void release(TextureManager& textureManager);
    sf::Vector2u getMapSizeInPixels();
    sf::Vector2u getMapSizeInTiles();
    sf::Vector2u getMapTileSize();
    std::string getSceneName();
    std::vector<std::shared_ptr<Collidable>>& getMapCollidables();
    std::vector<Collidable> getNpcCollidables();
    std::map<std::string, sf::IntRect> getNpcMoveBoundariesMap();
    std::map<std::string, std::string> getNpcNameToNpcAssetNameMap();
    Collidable getPlayerCollidable(std::string spawnName);
    std::string getPlayerSpawnPointName(std::string sceneName);

private:
    std::string sceneName;
    std::string tilesetImagePath;
    sf::Texture texture;
    sf::Vector2u mapSizeInPixels;
    sf::Vector2u mapSizeInTiles;
    sf::Vector2u tileSize;
    SceneObjectMap sceneObjectMap;
    TileMap tileMap;
    std::vector<sf::VertexArray> vertices;

    void loadTileMap(TextureManager& textureManager);
    static Logger logger;
};


#endif //NEWNEW_SCENE_H
