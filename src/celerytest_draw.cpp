#include "../include/celerytest_draw.hpp"
#include "../include/celerytest_con.hpp"

using namespace celerytest;

draw::gui::gui(U32 width, U32 height, bool fullscreen)
    : _width{width}, _height{height}, _fullscreen{fullscreen} {
  con::log(con::severity_t::echo, "Making a ", width, "x", height, " window\n");
  con::log(con::severity_t::echo, "Fullscreen = ", fullscreen, "\n");

  SetConfigFlags(FLAG_VSYNC_HINT | (fullscreen ? FLAG_FULLSCREEN_MODE : 0));
  InitWindow(width, height, "Celerytest " celerytest_VSTRING_FULL);
}

void draw::gui::enable_3d() {
  con::log(con::severity_t::echo, "Enabling 3D graphics\n");
  _data_3d = std::make_unique<data_3d>();
}

void draw::gui::disable_3d() {
  con::log(con::severity_t::echo, "Disabling 3D graphics\n");
  _data_3d = nullptr;
}

void draw::tick(draw::gui &gui) {
  BeginDrawing();

  ClearBackground(RAYWHITE);
  DrawFPS(20, 20);

  auto &&data_3d = gui.get_3d_data();
  if (data_3d != nullptr) {
    UpdateCamera(&data_3d->camera, CAMERA_FREE);

    BeginMode3D(data_3d->camera);
    DrawGrid(16, 1.0f);
    EndMode3D();
  }

  EndDrawing();
}

draw::gui::~gui() {
  con::log(con::severity_t::echo, "Removing GUI\n");
  CloseWindow();
}