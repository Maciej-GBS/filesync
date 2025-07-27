#pragma once

#include <cstdarg>
#include <sstream>
#include <stdio.h>
#include <string>
#include <type_traits>

#define FORMATSTR(obj) ::filesync::print(obj).c_str()

namespace filesync {

template <typename T, typename = void>
struct is_streamable : std::false_type {};

template <typename T>
struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T>())>> : std::true_type {};

template <typename T>
constexpr bool is_streamable_v = is_streamable<T>::value;

template <typename T>
std::enable_if_t<is_streamable_v<T>, std::string> print(const T& obj) {
    std::ostringstream oss;
    oss << obj;
    return oss.str();
}

inline std::string format(const char* baseStr, ...) {
    va_list args;
    char buffer[512];
    va_start(args, baseStr);
    vsprintf(buffer, baseStr, args);
    va_end(args);
    return std::string{buffer};
}

}
