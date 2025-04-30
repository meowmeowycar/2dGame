cmake_minimum_required(VERSION 3.28)
project(2dGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main
        src/main.cpp
        src/ImageDisplay.cpp
        src/ImageDisplay.h
        src/events.cpp
        src/events.h
        src/Player.cpp
        src/Player.h
        src/configuration.h
        src/functions.cpp
        src/functions.h
        src/FPS.cpp
        src/FPS.h
        src/Obstacle.cpp
        src/Obstacle.h
        src/HUD.cpp
        src/HUD.h
        src/Entity.cpp
        src/Entity.h
)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)