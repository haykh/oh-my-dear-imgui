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

  inline auto format(const char* format, ...) -> std::string {
    va_list args;
    va_start(args, format);
    int size = std::vsnprintf(nullptr, 0, format, args);
    va_end(args);
    if (size < 0) {
      return "Formatting error!";
    }
    std::vector<char> buffer(size + 1);
    va_start(args, format);
    std::vsnprintf(buffer.data(), buffer.size(), format, args);
    va_end(args);
    return std::string(buffer.data());
  }

} // namespace omdi::fmt

namespace omdi::logger {

  using Severity = plog::Severity;

  void Init(const Severity& = plog::debug);

  template <Severity S = plog::debug>
  inline void Log(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string msg = omdi::fmt::format(fmt, args);
    va_end(args);

    PLOG(S) << msg;
  }

  inline void Debug(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string msg = omdi::fmt::format(fmt, args);
    va_end(args);

    PLOG(plog::debug) << msg;
  }

  inline void Warning(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string msg = omdi::fmt::format(fmt, args);
    va_end(args);

    PLOG(plog::warning) << msg;
  }

  inline void Error(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string msg = omdi::fmt::format(fmt, args);
    va_end(args);

    PLOG(plog::error) << msg;
  }

  [[noreturn]]
  inline void Fatal(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string msg = omdi::fmt::format(fmt, args);
    va_end(args);

    PLOG(plog::fatal) << msg;
    throw std::runtime_error(msg);
  }

} // namespace omdi::logger

#endif // UTILS_H
