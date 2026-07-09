cmake_minimum_required(VERSION 3.20)
project(CS2_External_Cheat CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Shared
    ${CMAKE_CURRENT_SOURCE_DIR}/Security
    ${CMAKE_CURRENT_SOURCE_DIR}/Math
    ${CMAKE_CURRENT_SOURCE_DIR}/CS2Offsets
)

# 1. Build CS2_Core.exe
file(GLOB_RECURSE CORE_SOURCES 
    "Core/*.cpp" 
    "Core/*.hpp"
    "Shared/*.cpp"
    "Shared/*.hpp"
    "Math/*.cpp"
    "Math/*.hpp"
)
add_executable(CS2_Core ${CORE_SOURCES})

# 2. Build SteamOverlay_Render.dll
file(GLOB_RECURSE OVERLAY_SOURCES 
    "Overlay/*.cpp" 
    "Overlay/*.hpp"
    "Shared/*.cpp"
    "Shared/*.hpp"
    "Security/*.cpp"
    "Security/*.hpp"
)
add_library(SteamOverlay_Render SHARED ${OVERLAY_SOURCES})

# Link Windows libraries
target_link_libraries(CS2_Core PRIVATE dwmapi user32)
target_link_libraries(SteamOverlay_Render PRIVATE d3d11 user32)