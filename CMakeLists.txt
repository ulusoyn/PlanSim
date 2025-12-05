cmake_minimum_required(VERSION 3.14)
project(PlanetSim VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Fetch Content ---
include(FetchContent)

# --- Fetch Raylib ---
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        master
)

# --- Fetch ImGui (docking branch) ---
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        docking
)

FetchContent_MakeAvailable(raylib imgui)

# --- Add ImGui library ---
add_library(imgui_lib STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)

target_include_directories(imgui_lib PUBLIC
    ${imgui_SOURCE_DIR}
)

# --- Add rlImGui library ---
add_library(rlimgui STATIC
    external/rlimgui/src/rlImGui.cpp
)

target_include_directories(rlimgui PUBLIC
    external/rlimgui/include
)

# Link rlImGui with ImGui and raylib
target_link_libraries(rlimgui PUBLIC
    imgui_lib
    raylib
)

# --- 1. AUTOMATIC FILE DISCOVERY (Globbing) ---
# Scans the 'src' folder (and subfolders) for any .cpp file
# CONFIGURE_DEPENDS ensures it updates if you add new files later
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# --- Executable ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- 2. INCLUDE DIRECTORIES ---
# CMAKE_CURRENT_SOURCE_DIR ensures it looks in the folder where this script lives

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/core
    ${CMAKE_CURRENT_SOURCE_DIR}/include/physics
    ${CMAKE_CURRENT_SOURCE_DIR}/include/input
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rendering
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui
)

# --- Linking ---
target_link_libraries(${PROJECT_NAME} PRIVATE 
    raylib
    imgui_lib
    rlimgui
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm kernel32 shell32)
endif()

if (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread m)
endif()