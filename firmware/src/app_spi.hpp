#ifndef N1GP_APP_SPI_H
#define N1GP_APP_SPI_H

#include <igb_stm32/periph/gpio.hpp>
#include <igb_stm32/periph/spi.hpp>

typedef igb::stm32::Spi<igb::stm32::SpiType::spi1, igb::stm32::GpioPinType::pa7, igb::stm32::GpioPinType::pa6, igb::stm32::GpioPinType::pa5> AppSpi;

#endif /* N1GP_APP_SPI_H */
