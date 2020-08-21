#ifndef IGB_UTIL_CAST_H
#define IGB_UTIL_CAST_H

#include <type_traits>

namespace igb_util {
  template <typename T> T as(auto&& value) {
    return static_cast<T>(value);
  }

  template <typename T> auto enum_cast(const T& v) {
    return std::underlying_type<T>::type(v);
  }
}

#endif /* IGB_UTIL_CAST_H */
