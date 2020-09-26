#ifndef IGB_STM32_BASE_MCU_H
#define IGB_STM32_BASE_MCU_H

#include <igb_stm32/base/define.hpp>
#include <igb_util/macro.hpp>

// STM32_MCU_NAME の定義値に応じて、それぞれのMCU用のヘッダを include する
// -- 
// '.' がトークン扱いされないのは GCC 限定かもしれない
#define STM32_BASE_MCU_HPP_FILE(mcusym) <igb_stm32/base/mcu/UNWRAP(mcusym).hpp>
// '.' がトークン扱いされる環境だとこうか？
// #define _WRAPPING(name) name
// #define STM32_BASE_MCU_HPP_FILE(mcusym) <igb_stm32/device/mcu/_WRAPPING(mcusym) ## .hpp>

#include STM32_BASE_MCU_HPP_FILE(STM32_MCU)

#endif /* IGB_STM32_BASE_MCU_H */
