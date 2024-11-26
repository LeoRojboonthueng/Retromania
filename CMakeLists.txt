cmake_minimum_required(VERSION 3.11)

project(Retromania)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/lib/sfml")

include_directories(${SFML_DIR}/include)

add_subdirectory(${SFML_DIR})

set(SOURCES
    src/main.cpp
    src/core/Application.cpp
    src/states/MenuState.cpp
    src/states/PlayState.cpp
    src/states/PauseState.cpp
    src/states/StateStack.cpp
    src/entities/Player.cpp
    src/core/State.cpp)

include_directories(
    include
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)