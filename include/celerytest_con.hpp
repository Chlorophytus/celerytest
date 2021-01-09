#pragma once
#include "celerytest.hpp"
namespace celerytest {
/**
 * @brief Stores console-related code for the game engine.
 *
 */
namespace con {
/**
 * @brief Severities for logging. `fatal` should automatically throw/
 *
 */
enum class severity_t {
  echo = 0,
  warn,
  error,
  fatal,
};

/**
 * @brief An abstract base class for a console listener.
 * 
 */
struct listener {
  /**
   * @brief Pre-flight routines for console lines, usually prefixes to prepend
   * 
   * @param string The string to append to
   * @param severity The severity of the line to come
   */
  virtual void prelude(std::string &string, severity_t severity) = 0;

  /**
   * @brief Finalization routines for console lines, usually logging to I/O
   * 
   * @param string The string to log
   */
  virtual void finalize(std::string &string) = 0;

  /**
   * @brief End call for stringification
   * 
   * @param current The current string
   */
  void stringify(std::string &current) {}
  /**
   * @brief Stringify an argument
   * 
   * @tparam Ts C++14 template parameter pack for `more`
   * @param current The current string
   * @param head Any supported head parameter to unpack
   * @param more The tail of the parameter pack
   */
  template <class... Ts>
  void stringify(std::string &current, std::string head, Ts... more) {
    current += head;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, const char *head, Ts... more) {
    current += head;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, bool head, Ts... more) {
    current += head ? "true" : "false";
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, U8 head, Ts... more) {
    current += std::to_string(head);
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, U16 head, Ts... more) {
    current += std::to_string(head);
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, U32 head, Ts... more) {
    current += std::to_string(head);
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, U64 head, Ts... more) {
    current += std::to_string(head);
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, S8 head, Ts... more) {
    current += std::to_string(head);
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, S16 head, Ts... more) {
    current += head;
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, S32 head, Ts... more) {
    current += std::to_string(head);
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, S64 head, Ts... more) {
    current += std::to_string(head);
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, F32 head, Ts... more) {
    current += std::to_string(head);
    stringify(current, more...);
  }
  template <class... Ts>
  void stringify(std::string &current, F64 head, Ts... more) {
    current += std::to_string(head);
    stringify(current, more...);
  }

/**
 * @brief Log to only this listener.
 * 
 * @tparam Ts C++14 parameter pack for `more`
 * @param severity The severity of the line to log
 * @param more A parameter pack that contains the line's parts
 */
  template <class... Ts> void log(severity_t severity, Ts... more) {
    auto str = std::string{""};
    prelude(str, severity);
    stringify(str, more...);
    finalize(str);
  }
};
/**
 * @brief A listener that logs to `stderr`.
 * 
 */
struct terminal_listener : listener {
  void prelude(std::string &, severity_t);
  void finalize(std::string &);
};
using listener_list_t = std::vector<std::unique_ptr<listener>>;

/**
 * @brief Initialize all console structures.
 * 
 */
void initialize();

/**
 * @brief Get the vector consisting of all the active console listeners.
 * 
 * @return listener_list_t* const A vector of all the active console listeners
 */
listener_list_t *const listeners();

/**
 * @brief Clean up the console structures.
 * 
 */
void cleanup();

/**
 * @brief Log to all listeners.
 * 
 * @tparam Ts C++14 parameter pack for `more`
 * @param severity The severity of the line to log
 * @param more A parameter pack that contains the line's parts
 */
template <class... Ts> void log(severity_t severity, Ts... more) {
  auto l = listeners();
  assert(l != nullptr);
  for (auto &&listener : *l) {
    listener->log(severity, more...);
  }

  if (severity == severity_t::fatal) {
    // break here for any fatal error
    throw std::runtime_error{"a game engine assertion failed"};
  }
}
} // namespace con
} // namespace celerytest