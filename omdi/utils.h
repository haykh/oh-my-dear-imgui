#ifndef UTILS_H
#define UTILS_H

#include <GLFW/glfw3.h>
#include <plog/Log.h>

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

#endif // UTILS_H
