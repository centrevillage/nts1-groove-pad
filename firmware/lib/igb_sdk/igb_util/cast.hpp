#ifndef IGB_UTIL_CAST_H
#define IGB_UTIL_CAST_H

#include <type_traits>

namespace igb {
  template <typename T> static inline T as(auto&& value) {
    return static_cast<T>(value);
  }

  // TODO: コンパイルエラーになるので要修正
  template <typename T> static inline auto enum_cast(const T& v) {
    return std::underlying_type<T>::type(v);
  }
}

#endif /* IGB_UTIL_CAST_H */
