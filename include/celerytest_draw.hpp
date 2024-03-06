#pragma once
#include "celerytest.hpp"
namespace celerytest {
/**
 * @brief Stores drawing-related code for the game engine.
 *
 */
namespace draw {
/**
 * @brief When a gui is 3D, it needs this data
 *
 */
struct data_3d {
  Camera3D camera{ 0 }; /**< Player camera */
};

/**
 * @brief 2D window data. This must not have 3D object data.
 *
 */
class gui {
  U32 _width;
  U32 _height;
  bool _fullscreen;
  std::unique_ptr<data_3d> _data_3d{nullptr};

public:
  /**
   * @brief Try to return 3D objects data
   *
   * @return 3D objects data
   */
  std::unique_ptr<data_3d> &get_3d_data() {
    return _data_3d;
  }

  /**
   * @brief Create a GUI
   *
   * @param width the width of the GUI in pixels
   * @param height the height of the GUI in pixels
   * @param fullscreen true if fullscreen
   *
   */
  gui(U32 width, U32 height, bool fullscreen);

  /**
   * @brief Enable 3D rendering. Set the 3D data after calling.
   *
   *
   */
  void enable_3d();

  /**
   * @brief Disable 3D rendering
   *
   */
  void disable_3d();

  ~gui();

  // Copying/moving GUIs is disabled.
  // TODO: we might enable it later
  gui(gui &) = delete;
  gui(gui &&) = delete;
  gui &operator=(const gui &) = delete;
  gui &operator=(gui &&) = delete;
};

/**
 * @brief Draw the window singleton for one frame
 *
 * @param gui A 2D (`gui`) or 3D (`gui_3d`) GUI object
 *
 */
void tick(gui &gui);

/**
 * @brief Clean up the window singleton. This should not clean up Raylib.
 *
 */
void cleanup();
} // namespace draw
} // namespace celerytest