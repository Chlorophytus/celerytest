#pragma once
#include "celerytest.hpp"
namespace celerytest {
/**
 * @brief Stores OpenGL-related rendering code for the game engine.
 *
 */
namespace gl {
using window_t = SDL_Window;
using context_t = SDL_GLContext;

/**
 * @brief Initialize the window singleton
 *
 * @param width The width of the window in pixels
 * @param height The height of the window in pixels
 * @param fullscreen Flag for whether the window should be full-screen
 */
void window_initialize(U16 width, U16 height, bool fullscreen);

/**
 * @brief Refresh the OpenGL context.
 * 
 */
void tick();

/**
 * @brief Clean up the window singleton. This should not clean up SDL2.
 * 
 */
void window_cleanup();
} // namespace gl
} // namespace celerytest