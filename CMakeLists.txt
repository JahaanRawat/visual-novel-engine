cmake_minimum_required(VERSION 3.16)
project(VisualNovelGame LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set path for Homebrew on Apple Silicon Macs
if(APPLE)
    set(CMAKE_PREFIX_PATH "/opt/homebrew" ${CMAKE_PREFIX_PATH})
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/lib/cmake")
endif()

# Find required packages
find_package(PkgConfig REQUIRED)

# Find SDL3 packages
pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)
pkg_check_modules(SDL3_IMAGE REQUIRED IMPORTED_TARGET sdl3-image)
pkg_check_modules(SDL3_TTF REQUIRED IMPORTED_TARGET sdl3-ttf)

# Define include directories
set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL3_INCLUDE_DIRS}
    ${SDL3_IMAGE_INCLUDE_DIRS}
    ${SDL3_TTF_INCLUDE_DIRS}
)

# Define source files explicitly
set(HEADERS
    include/Game.h
    include/Character.h
    include/DialogueSystem.h
    include/ResourceManager.h
    include/SDLWrappers.h
    include/SDLManager.h
)

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Character.cpp
    src/DialogueSystem.cpp
    src/ResourceManager.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

# Link libraries using PkgConfig targets
target_link_libraries(${PROJECT_NAME} 
    PkgConfig::SDL3
    PkgConfig::SDL3_IMAGE
    PkgConfig::SDL3_TTF
)

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -Wall -Wextra -Wpedantic
        $<$<CONFIG:Debug>:-g -O0>
        $<$<CONFIG:Release>:-O3 -DNDEBUG>
    )
endif()

# Copy assets to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Set working directory for CLion
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# Print configuration info
message(STATUS "SDL3 found: ${SDL3_FOUND}")
message(STATUS "SDL3 include dirs: ${SDL3_INCLUDE_DIRS}")
message(STATUS "SDL3 libraries: ${SDL3_LIBRARIES}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")