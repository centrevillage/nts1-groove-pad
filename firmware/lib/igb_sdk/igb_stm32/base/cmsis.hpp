#ifndef IGB_STM32_BASE_CMSIS_H
#define IGB_STM32_BASE_CMSIS_H

#include <igb_stm32/base/common.hpp>

// F0
#if defined (STM32F0)     || defined (STM32F030x6) || defined (STM32F030x8) || \
    defined (STM32F031x6) || defined (STM32F038xx) ||                          \
    defined (STM32F042x6) || defined (STM32F048xx) || defined (STM32F070x6) || \
    defined (STM32F051x8) || defined (STM32F058xx) ||                          \
    defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || defined (STM32F070xB) || \
    defined (STM32F091xC) || defined (STM32F098xx) || defined (STM32F030xC)

#include "stm32f0xx.h"

#endif

// F1
#if defined (STM32F1)     || defined (STM32F100xB) || defined (STM32F100xE) || defined (STM32F101x6) || \
    defined (STM32F101xB) || defined (STM32F101xE) || defined (STM32F101xG) || defined (STM32F102x6) || \
    defined (STM32F102xB) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F103xE) || \
    defined (STM32F103xG) || defined (STM32F105xC) || defined (STM32F107xC)

#include "stm32f1xx.h"

#endif

// F2
#if defined (STM32F2) || defined (STM32F205xx) || defined (STM32F215xx) || defined (STM32F207xx) || defined (STM32F217xx)

#include "stm32f2xx.h"

#endif 

// F3
#if defined (STM32F3)     || defined (STM32F301x8) || defined (STM32F302x8) || defined (STM32F318xx) || \
    defined (STM32F302xC) || defined (STM32F303xC) || defined (STM32F358xx) || \
    defined (STM32F303x8) || defined (STM32F334x8) || defined (STM32F328xx) || \
    defined (STM32F302xE) || defined (STM32F303xE) || defined (STM32F398xx) || \
    defined (STM32F373xC) || defined (STM32F378xx)

#include "stm32f3xx.h"

#endif

// F4
#if defined (STM32F4)     || defined (STM32F405xx) || defined (STM32F415xx) || defined (STM32F407xx) || \
    defined (STM32F417xx) || defined (STM32F427xx) || defined (STM32F437xx) || defined (STM32F429xx) || \
    defined (STM32F439xx) || defined (STM32F401xC) || defined (STM32F401xE) || defined (STM32F410Tx) || \
    defined (STM32F410Cx) || defined (STM32F410Rx) || defined (STM32F411xE) || defined (STM32F446xx) || \
    defined (STM32F469xx) || defined (STM32F479xx) || defined (STM32F412Cx) || defined (STM32F412Rx) || \
    defined (STM32F412Vx) || defined (STM32F412Zx) || defined (STM32F413xx) || defined (STM32F423xx)

#include "stm32f4xx.h"

#endif

// F7
#if defined (STM32F7)     || defined (STM32F756xx) || defined (STM32F746xx) || defined (STM32F745xx) || \
    defined (STM32F767xx) || defined (STM32F769xx) || defined (STM32F777xx) || defined (STM32F779xx) || \
    defined (STM32F722xx) || defined (STM32F723xx) || defined (STM32F732xx) || defined (STM32F733xx) || \
    defined (STM32F730xx) || defined (STM32F750xx)

#include "stm32f7xx.h"

#endif

// G0
#if defined (STM32G0)     || defined (STM32G071xx) || defined (STM32G081xx) || defined (STM32G070xx) || \
    defined (STM32G030xx) || defined (STM32G031xx) || defined (STM32G041xx)

#include "stm32g0xx.h"

#endif

// G4
#if defined (STM32G4)     || defined (STM32G431xx) || defined (STM32G441xx) || \
    defined (STM32G471xx) || defined (STM32G473xx) || defined (STM32G474xx) || \
    defined (STM32G483xx) || defined (STM32G484xx) || defined (STM32GBK1CB)

#include "stm32g4xx.h"

#endif

// H7
#if defined (STM32H7)      || defined (STM32H743xx)  || defined (STM32H753xx)  || defined (STM32H750xx) || \
    defined (STM32H742xx)  || defined (STM32H745xx)  || defined (STM32H755xx)  || defined (STM32H747xx) || \
    defined (STM32H757xx)  || defined (STM32H7A3xx)  || defined (STM32H7A3xxQ) || defined (STM32H7B3xx) || \
    defined (STM32H7B3xxQ) || defined (STM32H7B0xx)  || defined (STM32H7B0xxQ)

#include "stm32h7xx.h"

#endif

#endif /* IGB_STM32_BASE_CMSIS_H */
