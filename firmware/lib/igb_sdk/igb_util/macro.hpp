#ifndef IGB_STM32_UTIL_MACRO_H
#define IGB_STM32_UTIL_MACRO_H

#define UNWRAP(id) id

#define IGB_FAST_INLINE inline __attribute__((always_inline, optimize("Ofast"))) 

#define MODIFY_REG_SIMPLE(reg, param_name, value) \
  MODIFY_REG(reg, param_name ## _Msk, static_cast<uint32_t>(value) << param_name ## _Pos);

#endif /* IGB_STM32_UTIL_MACRO_H */
