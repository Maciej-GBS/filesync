#pragma once

#include <string>
#include <sstream>
#include <type_traits>

#define FORMATSTRING(obj) ::filesync::print(obj).c_str()

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

inline std::string format(const char* baseStr, const char* tail) {
    std::ostringstream oss;
    oss << baseStr << tail;
    return oss.str();
}

}
