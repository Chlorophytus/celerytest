#pragma once
#include "celerytest.hpp"
namespace celerytest {
/**
 * @brief Stores console-related code for the game engine.
 *
 */
namespace con {
enum class severity_t {
  echo = 0,
  warn,
  error,
  fatal,
};
struct listener {
  virtual void prelude(std::string &, severity_t) = 0;
  virtual void finalize(std::string &) = 0;

  void stringify(std::string &current) {}
  template <class... Ts>
  void stringify(std::string &current, std::string str, Ts... more) {
    current += str;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, const char *str, Ts... more) {
    current += str;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, U8 num, Ts... more) {
    current += num;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, U16 num, Ts... more) {
    current += num;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, U32 num, Ts... more) {
    current += num;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, U64 num, Ts... more) {
    current += num;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, S8 num, Ts... more) {
    current += num;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, S16 num, Ts... more) {
    current += num;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, S32 num, Ts... more) {
    current += num;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, S64 num, Ts... more) {
    current += num;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, F32 num, Ts... more) {
    current += num;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, F64 num, Ts... more) {
    current += num;
    stringify(current, more...);
  }

  template <class... Ts> void log(severity_t severity, Ts... more) {
    auto str = std::string{""};
    prelude(str, severity);
    stringify(str, more...);
    finalize(str);
  }
};
struct terminal_listener : listener {
  void prelude(std::string &, severity_t);
  void finalize(std::string &);
};
using listener_list_t = std::vector<std::unique_ptr<listener>>;
void initialize();
listener_list_t *const listeners();
void cleanup();
template <class... Ts> void log(severity_t severity, Ts... more) {
  auto l = listeners();
  assert(l != nullptr);
  for (auto &&listener : *l) {
    listener->log(severity, more...);
  }
}
} // namespace con
} // namespace celerytest