cmake_minimum_required(VERSION 3.14)

project(PlanetSim VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Fetch Raylib ---
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(raylib)

# --- 1. AUTOMATIC FILE DISCOVERY (Globbing) ---
# Scans the 'src' folder (and subfolders) for any .cpp file
# CONFIGURE_DEPENDS ensures it updates if you add new files later
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# --- Executable ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- 2. INCLUDE DIRECTORIES ---
# CMAKE_CURRENT_SOURCE_DIR ensures it looks in the folder where this script lives
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
# --- Linking ---
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib winmm kernel32 shell32)
endif()

if (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread m)
endif()