cmake_minimum_required(VERSION 3.2)
project(newnew)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES src/main.cpp
        src/FramerateCounter.cpp
        src/asset/FontManager.cpp
        src/Game.cpp
        src/controller/BaseController.cpp
        src/controller/KeyboardController.cpp
        src/asset/TextureManager.cpp
        src/asset/BaseAssetManager.cpp
        src/asset/AssetPath.cpp
        src/entity/player/Player.cpp
        src/entity/character/Animation.cpp
        src/scene/Scene.cpp
        src/entity/character/AnimatedEntity.cpp
        src/collisions/Collidable.cpp
        src/entity/player/PlayerManager.cpp
        src/scene/SceneManager.cpp
        src/manager/TextManager.cpp
        src/manager/GameManager.cpp
        src/events/HandlerFunctionBase.cpp
        src/events/Event.cpp
        src/collisions/CollisionManager.cpp
        src/npc/NpcManager.cpp
        src/entity/character/NpcEntity.cpp
        src/scene/ObjectMap.cpp
        includes/scene/TileMap.cpp
        src/entity/character/MovableEntity.cpp
        src/entity/character/CollidableEntity.cpp)

set(INCLUDE_FILES includes/FramerateCounter.h
        includes/asset/FontManager.h
        includes/Game.h
        includes/controller/BaseController.h
        includes/controller/KeyboardController.h
        includes/asset/TextureManager.h
        includes/asset/BaseAssetManager.h
        includes/asset/AssetPath.h
        includes/entity/player/Player.h
        includes/entity/character/Animation.h
        includes/scene/Scene.h
        includes/entity/character/AnimatedEntity.h
        includes/collisions/Collidable.h
        includes/entity/player/PlayerManager.h
        includes/scene/SceneManager.h
        includes/manager/TextManager.h
        includes/manager/GameManager.h
        includes/events/Event.h
        includes/collisions/CollisionManager.h
        includes/npc/NpcManager.h
        includes/entity/character/NpcEntity.h
        includes/scene/ObjectMap.h
        includes/scene/TileMap.h
        includes/entity/character/MovableEntity.h
        includes/entity/character/CollidableEntity.h)

set(INCLUDE_ONLY_FILES includes/collisions/PlayerCollisionEvent.h
        includes/collisions/EntityCollisionEvent.h
        includes/controller/ControllerMoveEvent.h
        includes/collisions/CollidableType.h
        includes/controller/MoveDirection.h
        includes/events/EventBus.h
        includes/events/HandlerFunctionBase.h
        includes/events/MemberFunctionHandler.h
        includes/controller/ControllerMoveEvent.h
        includes/entity/character/EntityState.h
        includes/collisions/PlayerVicinityCollisionEvent.h
        includes/controller/ControllerActionEvent.h)

add_executable(newnew ${SOURCE_FILES} ${INCLUDE_FILES} ${INCLUDE_ONLY_FILES})

find_library(TMX_LITE_LIB lib/libtmxlite.a)
target_link_libraries(newnew ${TMX_LITE_LIB})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(newnew ${SFML_LIBRARIES})
endif()