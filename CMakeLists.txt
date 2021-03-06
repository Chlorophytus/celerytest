# Minimum CMake version is 3.19
cmake_minimum_required(VERSION 3.17)
# We are at v0.3.0, since v0.2 is Celerytest Legacy
project(celerytest VERSION 0.3.0.50)


# Configure this project
configure_file(include/${PROJECT_NAME}_cfg.in
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}_cfg.hpp)

# Find OpenGL
find_package(OpenGL REQUIRED)
# Find GLEW
find_package(GLEW REQUIRED)
# Find Lua 5.3
find_package(Lua 5.3 REQUIRED)
# Find the SDL2 package(s)
find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
# Find Doxygen
find_package(Doxygen)

# Find libpthread or the platform equivalent
find_package(Threads REQUIRED)

# Add the target
add_executable(${PROJECT_NAME}
    src/${PROJECT_NAME}_con.cpp
    src/${PROJECT_NAME}_gl.cpp
    src/${PROJECT_NAME}.cpp)

# Generate docs if we have it
doxygen_add_docs(docs)
# MSVC doesn't like post-C99 extensions
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED TRUE)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)
# Enable filthy C++17 extensions though
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED TRUE)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# GLEW, Lua, SDL2 headers
target_include_directories(${PROJECT_NAME} PRIVATE include ${LUA_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})
# Link!
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::OpenGL
    GLEW::GLEW
    ${LUA_LIBRARIES}
    Threads::Threads
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_LIBRARIES})