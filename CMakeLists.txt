cmake_minimum_required(VERSION 3.14)
project(shooter)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(FetchContent)

# SDL
FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.26.x
    GIT_SHALLOW TRUE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL)

# imgui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.89.3
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(imgui)

# shooter
file(GLOB imgui_sources
    ${imgui_SOURCE_DIR}/*.h
    ${imgui_SOURCE_DIR}/*.cpp)
file(GLOB imgui_backends
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer.cpp)
source_group(TREE ${imgui_SOURCE_DIR} PREFIX imgui FILES ${imgui_sources} ${imgui_backends})

file(GLOB_RECURSE sources src/*)
source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX src FILES ${sources})

add_executable(${PROJECT_NAME} WIN32
    ${sources}
    ${imgui_sources} ${imgui_backends})
target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /utf-8>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-W -Wall>)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:DEBUG>>:_CRTDBG_MAP_ALLOC>)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2 SDL2::SDL2main)