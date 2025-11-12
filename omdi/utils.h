#ifndef UTILS_H
#define UTILS_H

#include <GLFW/glfw3.h>
#include <plog/Log.h>

#include <chrono>
#include <cstdarg>
#include <stdexcept>
#include <string>
#include <vector>

namespace omdi::gl {

  void SetGLVersion(std::string&);

} // namespace omdi::gl

namespace omdi::fmt {

  inline auto vformat(const char* format, va_list args) -> std::string {
    va_list copy;
    va_copy(copy, args); // copy to avoid modifying original
    int size = std::vsnprintf(nullptr, 0, format, copy);
    va_end(copy);

    if (size < 0) {
      return "Formatting error!";
    }

    std::vector<char> buffer(size + 1);
    std::vsnprintf(buffer.data(), buffer.size(), format, args);
    return std::string(buffer.data());
  }

  inline auto format(const char* format, ...) -> std::string {
    va_list args;
    va_start(args, format);
    std::string result = vformat(format, args);
    va_end(args);
    return result;
  }

} // namespace omdi::fmt

namespace omdi::logger {

  using Severity = plog::Severity;

  void Init(const Severity& = plog::debug);

  template <Severity S = plog::debug>
  inline void Log(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string msg = omdi::fmt::vformat(fmt, args);
    va_end(args);

    PLOG(S) << msg;
  }

  inline void Debug(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    PLOG(plog::debug) << omdi::fmt::vformat(fmt, args);
    va_end(args);
  }

  inline void Warning(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    PLOG(plog::warning) << omdi::fmt::vformat(fmt, args);
    va_end(args);
  }

  inline void Error(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    PLOG(plog::error) << omdi::fmt::vformat(fmt, args);
    va_end(args);
  }

  [[noreturn]]
  inline void Fatal(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string msg = omdi::fmt::vformat(fmt, args);
    PLOG(plog::fatal) << msg;

    va_end(args);

    throw std::runtime_error(msg);
  }

} // namespace omdi::logger

namespace omdi::timer {

  class Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock>       m_now;
    const std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    std::size_t m_frame { 0u };
    double      m_delta { 1.0 };
    double      m_elapsed { 0.0 };

  public:
    Timer()
      : m_now { std::chrono::high_resolution_clock::now() }
      , m_start { m_now } {}

    void tick() {
      auto new_now = std::chrono::high_resolution_clock::now();
      m_elapsed    = std::chrono::duration<double>(new_now - m_start).count();
      m_delta      = std::chrono::duration<double>(new_now - m_now).count();
      m_now        = new_now;
      ++m_frame;
    }

    auto frame() const -> std::size_t {
      return m_frame;
    }

    auto delta() const -> double {
      return m_delta;
    }

    auto elapsed() const -> double {
      return m_elapsed;
    }
  };

} // namespace omdi::timer

#endif // UTILS_H
