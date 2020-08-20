#ifndef IGB_STM32_BASE_DEFINE_H
#define IGB_STM32_BASE_DEFINE_H

/* #!ruby
%W(
  STM32F030x6 STM32F030x8 STM32F031x6 STM32F038xx STM32F042x6
  STM32F048xx STM32F070x6 STM32F051x8 STM32F058xx STM32F071xB
  STM32F072xB STM32F078xx STM32F070xB STM32F091xC STM32F098xx STM32F030xC
  STM32F100xB STM32F100xE STM32F101x6 STM32F101xB STM32F101xE
  STM32F101xG STM32F102x6 STM32F102xB STM32F103x6 STM32F103xB
  STM32F103xE STM32F103xG STM32F105xC STM32F107xC
  STM32F205xx STM32F215xx STM32F207xx STM32F217xx
  STM32F301x8 STM32F302x8 STM32F318xx
  STM32F302xC STM32F303xC STM32F358xx
  STM32F303x8 STM32F334x8 STM32F328xx
  STM32F302xE STM32F303xE STM32F398xx
  STM32F373xC STM32F378xx
  STM32F405xx STM32F415xx STM32F407xx
  STM32F417xx STM32F427xx STM32F437xx STM32F429xx
  STM32F439xx STM32F401xC STM32F401xE STM32F410Tx
  STM32F410Cx STM32F410Rx STM32F411xE STM32F446xx
  STM32F469xx STM32F479xx STM32F412Cx STM32F412Rx
  STM32F412Vx STM32F412Zx STM32F413xx STM32F423xx
  STM32F756xx STM32F746xx STM32F745xx
  STM32F767xx STM32F769xx STM32F777xx STM32F779xx
  STM32F722xx STM32F723xx STM32F732xx STM32F733xx
  STM32F730xx STM32F750xx
  STM32G071xx STM32G081xx STM32G070xx
  STM32G030xx STM32G031xx STM32G041xx
  STM32G431xx STM32G441xx
  STM32G471xx STM32G473xx STM32G474xx
  STM32G483xx STM32G484xx
  STM32H743xx  STM32H753xx STM32H750xx
  STM32H742xx  STM32H745xx STM32H755xx  STM32H747xx
  STM32H757xx  STM32H7A3xx STM32H7A3xxQ STM32H7B3xx
  STM32H7B3xxQ STM32H7B0xx STM32H7B0xxQ
).each do |sym|
  print <<-EOS
#if defined(#{sym})
  #define STM32_SERIES          #{sym[0..6].downcase}
  #define STM32_MCU             #{sym.downcase}
  #define STM32_CMSIS_H_FILE    "#{sym[0..6].downcase}xx.h"
#endif
  EOS
end
*/

#if defined(STM32F030x6)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f030x6
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F030x8)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f030x8
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F031x6)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f031x6
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F038xx)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f038xx
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F042x6)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f042x6
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F048xx)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f048xx
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F070x6)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f070x6
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F051x8)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f051x8
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F058xx)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f058xx
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F071xB)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f071xb
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F072xB)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f072xb
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F078xx)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f078xx
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F070xB)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f070xb
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F091xC)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f091xc
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F098xx)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f098xx
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F030xC)
  #define STM32_SERIES          stm32f0
  #define STM32_MCU             stm32f030xc
  #define STM32_CMSIS_H_FILE    "stm32f0xx.h"
#endif
#if defined(STM32F100xB)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f100xb
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F100xE)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f100xe
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F101x6)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f101x6
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F101xB)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f101xb
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F101xE)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f101xe
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F101xG)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f101xg
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F102x6)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f102x6
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F102xB)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f102xb
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F103x6)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f103x6
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F103xB)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f103xb
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F103xE)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f103xe
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F103xG)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f103xg
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F105xC)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f105xc
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F107xC)
  #define STM32_SERIES          stm32f1
  #define STM32_MCU             stm32f107xc
  #define STM32_CMSIS_H_FILE    "stm32f1xx.h"
#endif
#if defined(STM32F205xx)
  #define STM32_SERIES          stm32f2
  #define STM32_MCU             stm32f205xx
  #define STM32_CMSIS_H_FILE    "stm32f2xx.h"
#endif
#if defined(STM32F215xx)
  #define STM32_SERIES          stm32f2
  #define STM32_MCU             stm32f215xx
  #define STM32_CMSIS_H_FILE    "stm32f2xx.h"
#endif
#if defined(STM32F207xx)
  #define STM32_SERIES          stm32f2
  #define STM32_MCU             stm32f207xx
  #define STM32_CMSIS_H_FILE    "stm32f2xx.h"
#endif
#if defined(STM32F217xx)
  #define STM32_SERIES          stm32f2
  #define STM32_MCU             stm32f217xx
  #define STM32_CMSIS_H_FILE    "stm32f2xx.h"
#endif
#if defined(STM32F301x8)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f301x8
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F302x8)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f302x8
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F318xx)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f318xx
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F302xC)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f302xc
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F303xC)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f303xc
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F358xx)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f358xx
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F303x8)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f303x8
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F334x8)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f334x8
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F328xx)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f328xx
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F302xE)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f302xe
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F303xE)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f303xe
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F398xx)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f398xx
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F373xC)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f373xc
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F378xx)
  #define STM32_SERIES          stm32f3
  #define STM32_MCU             stm32f378xx
  #define STM32_CMSIS_H_FILE    "stm32f3xx.h"
#endif
#if defined(STM32F405xx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f405xx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F415xx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f415xx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F407xx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f407xx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F417xx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f417xx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F427xx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f427xx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F437xx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f437xx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F429xx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f429xx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F439xx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f439xx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F401xC)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f401xc
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F401xE)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f401xe
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F410Tx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f410tx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F410Cx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f410cx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F410Rx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f410rx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F411xE)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f411xe
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F446xx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f446xx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F469xx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f469xx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F479xx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f479xx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F412Cx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f412cx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F412Rx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f412rx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F412Vx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f412vx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F412Zx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f412zx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F413xx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f413xx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F423xx)
  #define STM32_SERIES          stm32f4
  #define STM32_MCU             stm32f423xx
  #define STM32_CMSIS_H_FILE    "stm32f4xx.h"
#endif
#if defined(STM32F756xx)
  #define STM32_SERIES          stm32f7
  #define STM32_MCU             stm32f756xx
  #define STM32_CMSIS_H_FILE    "stm32f7xx.h"
#endif
#if defined(STM32F746xx)
  #define STM32_SERIES          stm32f7
  #define STM32_MCU             stm32f746xx
  #define STM32_CMSIS_H_FILE    "stm32f7xx.h"
#endif
#if defined(STM32F745xx)
  #define STM32_SERIES          stm32f7
  #define STM32_MCU             stm32f745xx
  #define STM32_CMSIS_H_FILE    "stm32f7xx.h"
#endif
#if defined(STM32F767xx)
  #define STM32_SERIES          stm32f7
  #define STM32_MCU             stm32f767xx
  #define STM32_CMSIS_H_FILE    "stm32f7xx.h"
#endif
#if defined(STM32F769xx)
  #define STM32_SERIES          stm32f7
  #define STM32_MCU             stm32f769xx
  #define STM32_CMSIS_H_FILE    "stm32f7xx.h"
#endif
#if defined(STM32F777xx)
  #define STM32_SERIES          stm32f7
  #define STM32_MCU             stm32f777xx
  #define STM32_CMSIS_H_FILE    "stm32f7xx.h"
#endif
#if defined(STM32F779xx)
  #define STM32_SERIES          stm32f7
  #define STM32_MCU             stm32f779xx
  #define STM32_CMSIS_H_FILE    "stm32f7xx.h"
#endif
#if defined(STM32F722xx)
  #define STM32_SERIES          stm32f7
  #define STM32_MCU             stm32f722xx
  #define STM32_CMSIS_H_FILE    "stm32f7xx.h"
#endif
#if defined(STM32F723xx)
  #define STM32_SERIES          stm32f7
  #define STM32_MCU             stm32f723xx
  #define STM32_CMSIS_H_FILE    "stm32f7xx.h"
#endif
#if defined(STM32F732xx)
  #define STM32_SERIES          stm32f7
  #define STM32_MCU             stm32f732xx
  #define STM32_CMSIS_H_FILE    "stm32f7xx.h"
#endif
#if defined(STM32F733xx)
  #define STM32_SERIES          stm32f7
  #define STM32_MCU             stm32f733xx
  #define STM32_CMSIS_H_FILE    "stm32f7xx.h"
#endif
#if defined(STM32F730xx)
  #define STM32_SERIES          stm32f7
  #define STM32_MCU             stm32f730xx
  #define STM32_CMSIS_H_FILE    "stm32f7xx.h"
#endif
#if defined(STM32F750xx)
  #define STM32_SERIES          stm32f7
  #define STM32_MCU             stm32f750xx
  #define STM32_CMSIS_H_FILE    "stm32f7xx.h"
#endif
#if defined(STM32G071xx)
  #define STM32_SERIES          stm32g0
  #define STM32_MCU             stm32g071xx
  #define STM32_CMSIS_H_FILE    "stm32g0xx.h"
#endif
#if defined(STM32G081xx)
  #define STM32_SERIES          stm32g0
  #define STM32_MCU             stm32g081xx
  #define STM32_CMSIS_H_FILE    "stm32g0xx.h"
#endif
#if defined(STM32G070xx)
  #define STM32_SERIES          stm32g0
  #define STM32_MCU             stm32g070xx
  #define STM32_CMSIS_H_FILE    "stm32g0xx.h"
#endif
#if defined(STM32G030xx)
  #define STM32_SERIES          stm32g0
  #define STM32_MCU             stm32g030xx
  #define STM32_CMSIS_H_FILE    "stm32g0xx.h"
#endif
#if defined(STM32G031xx)
  #define STM32_SERIES          stm32g0
  #define STM32_MCU             stm32g031xx
  #define STM32_CMSIS_H_FILE    "stm32g0xx.h"
#endif
#if defined(STM32G041xx)
  #define STM32_SERIES          stm32g0
  #define STM32_MCU             stm32g041xx
  #define STM32_CMSIS_H_FILE    "stm32g0xx.h"
#endif
#if defined(STM32G431xx)
  #define STM32_SERIES          stm32g4
  #define STM32_MCU             stm32g431xx
  #define STM32_CMSIS_H_FILE    "stm32g4xx.h"
#endif
#if defined(STM32G441xx)
  #define STM32_SERIES          stm32g4
  #define STM32_MCU             stm32g441xx
  #define STM32_CMSIS_H_FILE    "stm32g4xx.h"
#endif
#if defined(STM32G471xx)
  #define STM32_SERIES          stm32g4
  #define STM32_MCU             stm32g471xx
  #define STM32_CMSIS_H_FILE    "stm32g4xx.h"
#endif
#if defined(STM32G473xx)
  #define STM32_SERIES          stm32g4
  #define STM32_MCU             stm32g473xx
  #define STM32_CMSIS_H_FILE    "stm32g4xx.h"
#endif
#if defined(STM32G474xx)
  #define STM32_SERIES          stm32g4
  #define STM32_MCU             stm32g474xx
  #define STM32_CMSIS_H_FILE    "stm32g4xx.h"
#endif
#if defined(STM32G483xx)
  #define STM32_SERIES          stm32g4
  #define STM32_MCU             stm32g483xx
  #define STM32_CMSIS_H_FILE    "stm32g4xx.h"
#endif
#if defined(STM32G484xx)
  #define STM32_SERIES          stm32g4
  #define STM32_MCU             stm32g484xx
  #define STM32_CMSIS_H_FILE    "stm32g4xx.h"
#endif
#if defined(STM32H743xx)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h743xx
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif
#if defined(STM32H753xx)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h753xx
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif
#if defined(STM32H750xx)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h750xx
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif
#if defined(STM32H742xx)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h742xx
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif
#if defined(STM32H745xx)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h745xx
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif
#if defined(STM32H755xx)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h755xx
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif
#if defined(STM32H747xx)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h747xx
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif
#if defined(STM32H757xx)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h757xx
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif
#if defined(STM32H7A3xx)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h7a3xx
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif
#if defined(STM32H7A3xxQ)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h7a3xxq
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif
#if defined(STM32H7B3xx)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h7b3xx
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif
#if defined(STM32H7B3xxQ)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h7b3xxq
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif
#if defined(STM32H7B0xx)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h7b0xx
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif
#if defined(STM32H7B0xxQ)
  #define STM32_SERIES          stm32h7
  #define STM32_MCU             stm32h7b0xxq
  #define STM32_CMSIS_H_FILE    "stm32h7xx.h"
#endif

// 標準の命名規則から外れている
#if defined(STM32GBK1CB)
  #define STM32_SERIES          stm32g4
  #define STM32_CMSIS_H_FILE    "stm32g4xx.h"
  #define STM32_MCU_NAME        stm32gbk1cb
#endif

// 表記の揺らぎを吸収
#if !defined(ADC_COMMON) && defined(ADC1_COMMON)
#define ADC_COMMON ADC1_COMMON
#endif

#endif /* IGB_STM32_BASE_DEFINE_H */
