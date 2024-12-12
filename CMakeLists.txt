cmake_minimum_required(VERSION 3.11)

project(Retromania)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/lib/sfml")

include_directories(${SFML_DIR}/include)

add_subdirectory(${SFML_DIR})

include(FetchContent)

# Fetch nlohmann_json
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(nlohmann_json)

set(SOURCES
    src/main.cpp
    src/core/Application.cpp
    src/states/MenuState.cpp
    src/states/PlayState.cpp
    src/states/PauseState.cpp
    src/states/StateStack.cpp
    src/entities/Player.cpp 
    src/core/State.cpp
    src/entities/Platform.cpp
    src/states/SettingsState.cpp
    src/entities/Enemy.cpp)

include_directories(
    include
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    nlohmann_json::nlohmann_json
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)