cmake_minimum_required(VERSION 3.2)
project(newnew)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES src/main.cpp src/FramerateCounter.cpp src/asset/FontManager.cpp src/Game.cpp src/EventHandler.cpp
        src/controller/BaseController.cpp src/controller/KeyboardController.cpp src/asset/TextureManager.cpp
        src/asset/BaseAssetManager.cpp src/asset/FontPath.cpp src/asset/TexturePath.cpp
        src/entity/Entity.cpp src/entity/Player.cpp src/entity/Animation.cpp src/level/Level.cpp)

set(INCLUDE_FILES includes/FramerateCounter.h includes/asset/FontManager.h includes/Game.h includes/EventHandler.h
        includes/controller/BaseController.h includes/controller/KeyboardController.h includes/asset/TextureManager.h
        includes/asset/BaseAssetManager.h includes/asset/AssetPath.h includes/asset/FontPath.h includes/asset/TexturePath.h
        includes/entity/Entity.h includes/entity/Player.h includes/entity/Animation.h includes/level/Level.h)

add_executable(newnew ${SOURCE_FILES} ${INCLUDE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(newnew ${SFML_LIBRARIES})
endif()