# vim:set fenc=utf8
module NameConfig

  MCU_TO_SVD_MAPPING = {
    stm32f030x6: :STM32F030,
    stm32f030x8: :STM32F030,
    stm32f031x6: :STM32F030,
    stm32f038xx: :STM32F030,
    stm32f042x6: :STM32F042x,
    stm32f048xx: :STM32F042x,
    stm32f070x6: :STM32F0xx,
    stm32f051x8: :STM32F0xx,
    stm32f058xx: :STM32F0xx,
    stm32f071xb: :STM32F0xx,
    stm32f072xb: :STM32F072x,
    stm32f078xx: :STM32F072x,
    stm32f070xb: :STM32F0xx,
    stm32f091xc: :STM32F091x,
    stm32f098xx: :STM32F091x,
    stm32f030xc: :STM32F030,
    stm32f100xb: :STM32F100xx,
    stm32f100xe: :STM32F100xx,
    stm32f101x6: :STM32F101xx,
    stm32f101xb: :STM32F101xx,
    stm32f101xe: :STM32F101xx,
    stm32f101xg: :STM32F101xx,
    stm32f102x6: :STM32F102xx,
    stm32f102xb: :STM32F102xx,
    stm32f103x6: :STM32F103xx,
    stm32f103xb: :STM32F103xx,
    stm32f103xe: :STM32F103xx,
    stm32f103xg: :STM32F103xx,
    stm32f105xc: :STM32F105xx,
    stm32f107xc: :STM32F107xx,
    stm32f205xx: :STM32F20x,
    stm32f215xx: :STM32F21x,
    stm32f207xx: :STM32F20x,
    stm32f217xx: :STM32F21x,
    stm32f301x8: :STM32F301,
    stm32f302x8: :STM32F302,
    stm32f318xx: :STM32F301,
    stm32f302xc: :STM32F302,
    stm32f303xc: :STM32F303,
    stm32f358xx: :STM32F3x8,
    stm32f303x8: :STM32F303,
    stm32f334x8: :STM32F3x4,
    stm32f328xx: :STM32F3x8,
    stm32f302xe: :STM32F302,
    stm32f303xe: :STM32F303,
    stm32f398xx: :STM32F3x8,
    stm32f373xc: :STM32F373,
    stm32f378xx: :STM32F3x8,
    stm32f405xx: :STM32F405,
    stm32f415xx: :STM32F405, # 対応するファイルがないが、とりあえず
    stm32f407xx: :STM32F407,
    stm32f417xx: :STM32F407, # 対応するファイルがないが、とりあえず
    stm32f427xx: :STM32F427,
    stm32f437xx: :STM32F407, # 対応するファイルがないが、とりあえず
    stm32f429xx: :STM32F429,
    stm32f439xx: :STM32F427,
    stm32f401xc: :STM32F401,
    stm32f401xe: :STM32F401,
    stm32f410tx: :STM32F410,
    stm32f410cx: :STM32F410,
    stm32f410rx: :STM32F410,
    stm32f411xe: :STM32F411,
    stm32f446xx: :STM32F446,
    stm32f469xx: :STM32F469,
    stm32f479xx: :STM32F469, # 対応するファイルがないが、とりあえず
    stm32f412cx: :STM32F412,
    stm32f412rx: :STM32F412,
    stm32f412vx: :STM32F412,
    stm32f412zx: :STM32F412,
    stm32f413xx: :STM32F413,
    stm32f423xx: :STM32F423, # 対応するファイルがないが、とりあえず
    stm32f756xx: :STM32F7x6,
    stm32f746xx: :STM32F7x6,
    stm32f745xx: :STM32F745,
    stm32f767xx: :STM32F7x7,
    stm32f769xx: :STM32F7x9,
    stm32f777xx: :STM32F7x7,
    stm32f779xx: :STM32F7x9,
    stm32f722xx: :STM32F7x2,
    stm32f723xx: :STM32F7x3,
    stm32f732xx: :STM32F7x2,
    stm32f733xx: :STM32F7x3,
    stm32f730xx: :STM32F730,
    stm32f750xx: :STM32F750,
    stm32g071xx: :STM32G07x,
    stm32g081xx: :STM32G07x, # 対応するファイルがないが、とりあえず
    stm32g070xx: :STM32G07x,
    stm32g030xx: :STM32G07x, # 対応するファイルがないが、とりあえず
    stm32g031xx: :STM32G07x, # 対応するファイルがないが、とりあえず
    stm32g041xx: :STM32G07x, # 対応するファイルがないが、とりあえず
    stm32g431xx: :STM32G431xx,
    stm32g441xx: :STM32G441xx,
    stm32g471xx: :STM32G471xx,
    stm32g473xx: :STM32G473xx,
    stm32g474xx: :STM32G474xx,
    stm32g483xx: :STM32G483xx,
    stm32g484xx: :STM32G484xx,
    stm32gbk1cb: :STM32GBK1CBT6,
    stm32h743xx: :STM32H743x,
    stm32h753xx: :STM32H753x,
    stm32h750xx: :STM32H750x,
    stm32h742xx: :STM32H742x,
    stm32h745xx: :STM32H7x5_CM7, # 本来は、二つのMCUそれぞれを定義しないとだめだが、とりあえず
    stm32h755xx: :STM32H7x5_CM7, # 本来は、二つのMCUそれぞれを定義しないとだめだが、とりあえず
    stm32h747xx: :STM32H7x7_CM7, # 本来は、二つのMCUそれぞれを定義しないとだめだが、とりあえず
    stm32h757xx: :STM32H7x7_CM7, # 本来は、二つのMCUそれぞれを定義しないとだめだが、とりあえず
    stm32h7a3xx: :STM32H7A3x,
    stm32h7a3xxq: :STM32H7A3x,
    stm32h7b3xx: :STM32H7B3x,
    stm32h7b3xxq: :STM32H7B3x,
    stm32h7b0xx: :STM32H7B3x, # 対応するファイルがないが、とりあえず
    stm32h7b0xxq: :STM32H7B3x, # 対応するファイルがないが、とりあえず
  }.freeze

  AVAILABLE_MCU = MCU_TO_SVD_MAPPING.keys.freeze

  def self.available_mcu
    AVAILABLE_MCU
  end

  def self.mcu_to_svd(mcu_name)
    MCU_TO_SVD_MAPPING[mcu_name.to_sym]
  end
end
