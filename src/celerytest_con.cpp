#include "../include/celerytest_con.hpp"

using namespace celerytest;

static auto listener_list = std::unique_ptr<con::listener_list_t>{nullptr};

void con_raylib_hook(int msg_type, const char *text, va_list args) {
  constexpr auto BUFFER_SIZE = 1024;
  char text_buffer[BUFFER_SIZE]{0};
  vsnprintf(text_buffer, BUFFER_SIZE, text, args);

  switch (msg_type) {
  case LOG_DEBUG:
  case LOG_INFO:
    con::log(con::severity_t::echo, text_buffer, "\n");
    break;
  case LOG_WARNING:
    con::log(con::severity_t::warn, text_buffer, "\n");
    break;
  case LOG_ERROR:
    con::log(con::severity_t::error, text_buffer, "\n");
    break;
  default:
    break;
  }
}

void con::terminal_listener::prelude(std::string &string,
                                     con::severity_t severity) {
  // We should set HH:MM:SS.III
  auto format = std::stringstream{};
  format << "[";
  auto t = std::chrono::system_clock::now();
  auto t_time = std::chrono::system_clock::to_time_t(t);
  char t_buffer[64]{0};
  std::strftime(t_buffer, sizeof(char) * 63, "%T", std::localtime(&t_time));
  auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
                    t.time_since_epoch())
                    .count() %
                1000;
  format << t_buffer;
  format << ".";
  format << std::setw(3) << std::setfill('0') << millis;
  format << std::setw(0) << std::setfill(' ') << "] ";
  switch (severity) {
  case con::severity_t::echo: {
    format << "[ .. ] ";
    break;
  }
  case con::severity_t::warn: {
    format << "[ ?? ] ";
    break;
  }
  case con::severity_t::error: {
    format << "[ !! ] ";
    break;
  }
  case con::severity_t::fatal: {
    format << "[ ## ] ";
    break;
  }
  }
  string += format.str();
}

void con::terminal_listener::finalize(std::string &string) {
  std::fprintf(stderr, "%s", string.c_str());
}

void con::initialize() {
  listener_list = std::make_unique<listener_list_t>();
  SetTraceLogCallback(con_raylib_hook);
}
con::listener_list_t *const con::listeners() { return listener_list.get(); }
void con::cleanup() { listener_list = nullptr; }
