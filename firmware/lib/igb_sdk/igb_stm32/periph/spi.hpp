#ifndef IGB_STM32_PERIPH_SPI_H
#define IGB_STM32_PERIPH_SPI_H

#include <igb_stm32/base.hpp>
#include <igb_util/cast.hpp>
#include <igb_stm32/periph/gpio.hpp>
#include <igb_stm32/periph/rcc.hpp>
#include <igb_util/macro.hpp>

namespace igb {
namespace stm32 {

enum class SpiMode : uint32_t {
  SLAVE  = 0,
  MASTER = (SPI_CR1_MSTR | SPI_CR1_SSI),
};

enum class SpiStandard : uint32_t {
  MOTOROLA = 0,
  TI = SPI_CR2_FRF,
};

enum class SpiClockPhase : uint32_t {
  ONE_EDGE = 0,
  TWO_EDGE = SPI_CR1_CPHA,
};

enum class SpiClockPolarity : uint32_t {
  LOW = 0,
  HIGH = SPI_CR1_CPOL
};

enum class SpiBaudratePrescaler : uint32_t {
  DIV2 = 0,
  DIV4 = SPI_CR1_BR_0,
  DIV8 = SPI_CR1_BR_1,
  DIV16 = SPI_CR1_BR_1 | SPI_CR1_BR_0,
  DIV32 = SPI_CR1_BR_2,
  DIV64 = SPI_CR1_BR_2 | SPI_CR1_BR_0,
  DIV128 = SPI_CR1_BR_2 | SPI_CR1_BR_1,
  DIV256 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
};

enum class SpiBitOrder : uint32_t {
  MSB_FIRST = 0,
  LSB_FIRST = SPI_CR1_LSBFIRST,
};

enum class SpiTransDir : uint32_t {
  FULL_DUPLEX = 0,
  SIMPLEX_RX  = SPI_CR1_RXONLY,
  HALF_DUPLEX_RX = SPI_CR1_BIDIMODE,
  HALF_DUPLEX_TX = SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE,
};

enum class SpiDataWidth : uint32_t {
  _4BIT = SPI_CR2_DS_0 | SPI_CR2_DS_1,
  _5BIT = SPI_CR2_DS_2,
  _6BIT = SPI_CR2_DS_2 | SPI_CR2_DS_0,
  _7BIT = SPI_CR2_DS_2 | SPI_CR2_DS_1,
  _8BIT = SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0,
  _9BIT = SPI_CR2_DS_3,
  _10BIT = SPI_CR2_DS_3 | SPI_CR2_DS_0,
  _11BIT = SPI_CR2_DS_3 | SPI_CR2_DS_1,
  _12BIT = SPI_CR2_DS_3 | SPI_CR2_DS_1 | SPI_CR2_DS_0,
  _13BIT = SPI_CR2_DS_3 | SPI_CR2_DS_2,
  _14BIT = SPI_CR2_DS_3 | SPI_CR2_DS_2 | SPI_CR2_DS_0,
  _15BIT = SPI_CR2_DS_3 | SPI_CR2_DS_2 | SPI_CR2_DS_1,
  _16BIT = SPI_CR2_DS_3 | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0,
};

enum class SpiFifoThreshold : uint32_t {
  HALF = 0,
  QUARTER = SPI_CR2_FRXTH,
};

enum class SpiCrcWidth : uint32_t {
  _8BIT = 0,
  _16BIT = SPI_CR1_CRCL,
};

enum class SpiNssMode : uint32_t {
  HARD_INPUT  = 0,
  HARD_OUTPUT = SPI_CR1_SSM,
  SOFT        = SPI_CR1_SSM,
};

enum class SpiState : uint32_t {
  RX_BUF_NOT_EMPTY   = SPI_SR_RXNE,
  TX_BUF_EMPTY       = SPI_SR_TXE,
  BUSY               = SPI_SR_BSY,
  CRC_ERROR          = SPI_SR_CRCERR,
  MODE_FAULT         = SPI_SR_MODF,
  OVERRUN            = SPI_SR_OVR,
  FRAME_FORMAT_ERROR = SPI_SR_FRE,
};

enum class SpiInterruptType : uint32_t {
  RX_BUF_NOT_EMPTY = SPI_CR2_RXNEIE,
  TX_BUF_EMPTY     = SPI_CR2_TXEIE,
  ERROR            = SPI_CR2_ERRIE,
};

enum class SpiDmaReqTarget : uint32_t {
  RX = SPI_CR2_RXDMAEN,
  TX = SPI_CR2_TXDMAEN,
};

enum class SpiDmaParityTarget : uint32_t {
  RX = SPI_CR2_RXDMAEN,
  TX = SPI_CR2_TXDMAEN,
};

enum class SpiDmaParityType : uint32_t {
  EVEN = 0,
  ODD  = 1,
};

struct Spi {
  const SpiType type;
  SPI_TypeDef* p_spi;

  IGB_FAST_INLINE void enable() {
    p_spi->CR1 |= SPI_CR1_SPE;
  }

  IGB_FAST_INLINE void disable() {
    p_spi->CR1 &= ~SPI_CR1_SPE;
  }

  IGB_FAST_INLINE void setMode(SpiMode mode) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_MSTR | SPI_CR1_SSI, as<uint32_t>(mode));
  }

  IGB_FAST_INLINE void setStandard(SpiStandard standard) {
    MODIFY_REG(p_spi->CR2, SPI_CR2_FRF, as<uint32_t>(standard));
  }

  IGB_FAST_INLINE void setClockPhase(SpiClockPhase phase) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_CPHA, as<uint32_t>(phase));
  }

  IGB_FAST_INLINE void setClockPolarity(SpiClockPolarity polarity) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_CPOL, as<uint32_t>(polarity));
  }

  IGB_FAST_INLINE void setBaudratePrescaler(SpiBaudratePrescaler prescaler) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_BR, as<uint32_t>(prescaler));
  }

  IGB_FAST_INLINE void setTransBitOrder(SpiBitOrder order) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_LSBFIRST, as<uint32_t>(order));
  }

  IGB_FAST_INLINE void setTransDir(SpiTransDir dir) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_RXONLY | SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE, as<uint32_t>(dir));
  }

  IGB_FAST_INLINE void setDataWidth(SpiDataWidth data_width) {
    MODIFY_REG(p_spi->CR2, SPI_CR2_DS, as<uint32_t>(data_width));
  }

  IGB_FAST_INLINE void setRxFifoThreshold(SpiFifoThreshold threshold) {
    MODIFY_REG(p_spi->CR2, SPI_CR2_FRXTH, as<uint32_t>(threshold));
  }

  IGB_FAST_INLINE void setCrc(bool enable) {
    if (enable) {
      p_spi->CR1 |= SPI_CR1_CRCEN;
    } else {
      p_spi->CR1 &= ~SPI_CR1_CRCEN;
    }
  }

  IGB_FAST_INLINE void setCrcWidth(SpiCrcWidth width) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_CRCL, as<uint32_t>(width));
  }

  IGB_FAST_INLINE void setCrcNext() {
    p_spi->CR1 |= SPI_CR1_CRCNEXT;
  }

  IGB_FAST_INLINE void setCrcPolynomial(uint32_t poly) {
    p_spi->CRCPR = (uint16_t)poly;
  }

  IGB_FAST_INLINE uint32_t getRxCrc() {
    return (uint32_t)(p_spi->RXCRCR);
  }

  IGB_FAST_INLINE uint32_t getTxCrc() {
    return (uint32_t)(p_spi->TXCRCR);
  }

  IGB_FAST_INLINE void setNssMode(SpiNssMode mode) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_SSM,  as<uint32_t>(mode));
    MODIFY_REG(p_spi->CR2, SPI_CR2_SSOE, ((uint32_t)(as<uint32_t>(mode) >> 16U)));
  }

  IGB_FAST_INLINE void setNssPulseMng(bool enable) {
    if (enable) {
      p_spi->CR2 |= SPI_CR2_NSSP;
    } else {
      p_spi->CR2 &= ~SPI_CR2_NSSP;
    }
  }

  IGB_FAST_INLINE bool isState(SpiState state) {
    return !!(p_spi->SR & as<uint32_t>(state));
  }
  
  IGB_FAST_INLINE void clearState(SpiState state) {
    CLEAR_BIT(p_spi->SR, as<uint32_t>(state));
  }

  IGB_FAST_INLINE void enableInterrupt(SpiInterruptType type) {
    p_spi->CR2 |= as<uint32_t>(type);
  }

  IGB_FAST_INLINE void disableInterrupt(SpiInterruptType type) {
    p_spi->CR2 &= ~(as<uint32_t>(type));
  }

  IGB_FAST_INLINE void enableDmaReq(SpiDmaReqTarget type) {
    p_spi->CR2 |= as<uint32_t>(type);
  }

  IGB_FAST_INLINE void disableDmaReq(SpiDmaReqTarget type) {
    p_spi->CR2 &= ~(as<uint32_t>(type));
  }

  IGB_FAST_INLINE void setDmaParity(SpiDmaParityTarget target, SpiDmaParityType type) {
    switch (target) {
      case SpiDmaParityTarget::TX:
        MODIFY_REG(p_spi->CR2, SPI_CR2_LDMATX, (as<uint32_t>(type) << SPI_CR2_LDMATX_Pos));
        break;
      case SpiDmaParityTarget::RX:
        MODIFY_REG(p_spi->CR2, SPI_CR2_LDMARX, (as<uint32_t>(type) << SPI_CR2_LDMARX_Pos));
        break;
    }
  }

  IGB_FAST_INLINE uint32_t getRegAddr() {
    return (uint32_t) &(p_spi->DR);
  }

  IGB_FAST_INLINE uint8_t receiveU8() {
    return (uint8_t)(p_spi->DR);
  }

  IGB_FAST_INLINE uint16_t receiveU16() {
    return (uint16_t)(p_spi->DR);
  }

  IGB_FAST_INLINE void sendU8(uint8_t data) {
#if defined (__GNUC__)
    __IO uint8_t *spidr = ((__IO uint8_t *)&p_spi->DR);
    *spidr = data;
#else
    *((__IO uint8_t *)&p_spi->DR) = data;
#endif /* __GNUC__ */
  }

  IGB_FAST_INLINE void sendU16(uint16_t data) {
#if defined (__GNUC__)
  __IO uint16_t *spidr = ((__IO uint16_t *)&p_spi->DR);
  *spidr = data;
#else
  p_spi->DR = data;
#endif /* __GNUC__ */
  }

  IGB_FAST_INLINE uint8_t transferU8sync(uint8_t data) {
    while (isState(SpiState::BUSY));
    while (!isState(SpiState::TX_BUF_EMPTY));
    sendU8(data);
    while (!isState(SpiState::RX_BUF_NOT_EMPTY));
    return receiveU8();
  }

  static IGB_FAST_INLINE Spi newSpi(const SpiType spi_type) {
    return Spi {
      .type = spi_type,
      .p_spi = STM32_PERIPH_INFO.spi[as<uint8_t>(spi_type)].p_spi
    };
  }

  IGB_FAST_INLINE void prepareGpio(GpioPinType pin_type) {
    auto periph_type = as_periph_type(type);
    if (!periph_type) { return; }

    auto result = get_af_idx(periph_type.value(), pin_type);
    if (!result) { return; }

    GpioType gpio_type = extract_gpio_type(pin_type);
    GpioPin pin = GpioPin::newPin(pin_type);
    pin.setMode(GpioMode::ALTERNATE);
    pin.setPullMode(GpioPullMode::NO);
    pin.setSpeedMode(GpioSpeedMode::HIGH);
    pin.setOutputMode(GpioOutputMode::PUSHPULL);
    pin.setAlternateFunc(result.value());
  }

  IGB_FAST_INLINE void prepareSpiMaster(GpioPinType mosi_pin, GpioPinType miso_pin, GpioPinType sck_pin, SpiBaudratePrescaler prescaler) {
    const auto& spi_info = STM32_PERIPH_INFO.spi[as<uint8_t>(type)];
    spi_info.bus.enableBusClock();
    prepareGpio(mosi_pin);
    prepareGpio(miso_pin);
    prepareGpio(sck_pin);

    setTransDir(SpiTransDir::FULL_DUPLEX);
    setMode(SpiMode::MASTER);
    setDataWidth(SpiDataWidth::_8BIT);
    setClockPolarity(SpiClockPolarity::LOW);
    setClockPhase(SpiClockPhase::ONE_EDGE);
    setNssMode(SpiNssMode::SOFT);
    setBaudratePrescaler(prescaler);
    setTransBitOrder(SpiBitOrder::MSB_FIRST);
    setCrc(false);
    setCrcPolynomial(7);
    setStandard(SpiStandard::MOTOROLA);
    setRxFifoThreshold(SpiFifoThreshold::QUARTER);
    setNssPulseMng(true);
    enable();
  }

};

}
}

#endif /* IGB_STM32_PERIPH_SPI_H */
