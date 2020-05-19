cmake_minimum_required(VERSION 3.2)
project(newnew)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        src/main.cpp
        src/util/FramerateCounter.cpp
        src/asset/FontManager.cpp
        src/Game.cpp
        src/controller/BaseController.cpp
        src/controller/KeyboardController.cpp
        src/asset/TextureManager.cpp
        src/asset/BaseAssetManager.cpp
        src/asset/AssetPath.cpp
        src/entity/player/PlayerEntity.cpp
        src/entity/components/Animation.cpp
        src/scene/Scene.cpp
        src/entity/components/EntityAnimation.cpp
        src/collisions/Collidable.cpp
        src/scene/SceneManager.cpp
        src/ui/dialogue/DialogueManager.cpp
        src/events/HandlerFunctionBase.cpp
        src/events/Event.cpp
        src/collisions/CollisionManager.cpp
        src/npc/NpcManager.cpp
        src/entity/npc/NpcEntity.cpp
        src/map/TileMap.cpp
        src/entity/components/EntityMovement.cpp
        src/entity/components/EntityCollidable.cpp
        src/scene/ViewManager.cpp
        src/ui/dialogue/DialogueEvent.cpp
        src/ui/dialogue/Dialogue.cpp
        src/ui/dialogue/DialoguePiece.cpp
        src/entity/components/EntityAutonomousMovement.cpp
        src/util/Logger.cpp
        src/entity/components/EntityLogger.cpp
        src/util/XmlManager.cpp
        src/ui/manager/UIManager.cpp
        src/map/SceneMap.cpp
        src/ui/component/menu_component/MenuWithSelectorComponent.cpp
        src/ui/component/MenuOptionComponent.cpp
        src/map/MapLoader.cpp
        src/map/Map.cpp
        src/ui/component/menu_component/DialogueMenuComponent.cpp
        src/ui/UIComponentInitializer.cpp
        src/ui/component/menu_component/BaseMenuComponent.cpp
        src/collisions/CollisionPublisher.cpp
        src/collisions/CollisionUtil.cpp
        src/scene/OverworldScene.cpp
        src/scene/BattleScene.cpp
        src/scene/SceneStateHandler.cpp
        src/ui/manager/OverworldUIManager.cpp
        src/ui/manager/BattleUIManager.cpp
        src/scene/battle/BattleSceneMenuChoice.cpp
        src/scene/overworld/OverworldStartMenuChoice.cpp
        src/ui/dialogue/DialogueSubstitutionUtil.cpp
        src/scene/PlayerManager.cpp
        )

set(INCLUDE_FILES
        includes/util/FramerateCounter.h
        includes/asset/FontManager.h
        includes/Game.h
        includes/controller/BaseController.h
        includes/controller/KeyboardController.h
        includes/asset/TextureManager.h
        includes/asset/BaseAssetManager.h
        includes/asset/AssetPath.h
        includes/entity/player/PlayerEntity.h
        includes/entity/components/Animation.h
        includes/scene/Scene.h
        includes/entity/components/EntityAnimation.h
        includes/collisions/Collidable.h
        includes/scene/SceneManager.h
        includes/ui/dialogue/DialogueManager.h
        includes/events/Event.h
        includes/collisions/CollisionManager.h
        includes/npc/NpcManager.h
        includes/entity/npc/NpcEntity.h
        includes/map/TileMap.h
        includes/entity/components/EntityMovement.h
        includes/entity/components/EntityCollidable.h
        includes/scene/ViewManager.h
        includes/ui/dialogue/DialogueEvent.h
        includes/ui/dialogue/Dialogue.h
        includes/ui/dialogue/DialoguePiece.h
        includes/entity/components/EntityAutonomousMovement.h
        includes/util/Logger.h
        includes/entity/components/EntityLogger.h
        includes/util/XmlManager.h
        includes/ui/manager/UIManager.h
        includes/map/SceneMap.h
        includes/ui/component/menu_component/MenuWithSelectorComponent.h
        includes/ui/component/MenuOptionComponent.h
        includes/map/MapLoader.h
        includes/map/Map.h
        includes/ui/component/menu_component/DialogueMenuComponent.h
        includes/ui/UIComponentInitializer.h
        includes/ui/component/menu_component/BaseMenuComponent.h
        includes/collisions/CollisionPublisher.h
        includes/collisions/CollisionUtil.h
        includes/scene/OverworldScene.h
        includes/scene/BattleScene.h
        includes/scene/SceneStateHandler.h
        includes/ui/manager/OverworldUIManager.h
        includes/ui/manager/BattleUIManager.h
        includes/scene/battle/BattleSceneMenuChoice.h
        includes/scene/overworld/OverworldStartMenuChoice.h
        includes/ui/dialogue/DialogueSubstitutionUtil.h
        includes/scene/PlayerManager.h
        )

set(INCLUDE_ONLY_FILES includes/events/event/PlayerCollisionEvent.h
        includes/events/event/EntityCollisionEvent.h
        includes/events/event/ControllerMoveEvent.h
        includes/map/ObjectType.h
        includes/controller/MoveDirection.h
        includes/events/EventBus.h
        includes/events/HandlerFunctionBase.h
        includes/events/MemberFunctionHandler.h
        includes/events/event/ControllerMoveEvent.h
        includes/entity/components/EntityState.h
        includes/events/event/PlayerVicinityCollisionEvent.h
        includes/events/event/ControllerActionEvent.h
        includes/events/event/OpenDialogueEvent.h
        includes/events/event/CloseDialogueEvent.h
        includes/events/event/PlayerPositionChangeEvent.h
        includes/events/event/ExitGameEvent.h
        includes/events/event/NpcCollisionEvent.h
        includes/scene/SceneState.h
        includes/events/event/PlayerDoorCollisionEvent.h
        includes/events/event/ControllerMenuEvent.h
        includes/events/event/ControllerCancelEvent.h
        includes/events/event/ControllerMenuMoveEvent.h
        includes/ui/component/MenuScreenPosition.h
        includes/ui/UIComponentType.h
        includes/entity/npc/types/MonsterNpcEntity.h
        includes/entity/npc/types/NpcType.h
        includes/entity/npc/types/HumanNpcEntity.h
        includes/entity/npc/types/CatNpcEntity.h
        includes/events/event/PlayerAndNpcCollisionEvent.h
        includes/events/event/ChangeSceneToNewMapEvent.h
        includes/events/event/ChangeSceneToBattleEvent.h
        includes/scene/battle/BattleSceneDialogueEventName.h
        includes/scene/battle/BattleState.h
        includes/events/event/ChangeSceneToPreviousSceneEvent.h
        includes/scene/overworld/OverworldState.h)

add_executable(newnew ${SOURCE_FILES} ${INCLUDE_FILES} ${INCLUDE_ONLY_FILES})

find_library(TMX_LITE_LIB lib/libtmxlite.a)
target_link_libraries(newnew ${TMX_LITE_LIB})

find_library(TINY_XML2_LIB lib/libtinyxml2.7.0.1.dylib)
target_link_libraries(newnew ${TINY_XML2_LIB})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(newnew ${SFML_LIBRARIES})
endif()