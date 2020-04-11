#ifndef __N1GP_OLED_SPI_H__
#define __N1GP_OLED_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32_def.h"
#include "PeripheralPins.h"
#include "PinAF_STM32F1.h"
#include "pinconfig.h"

void oled_spi_setup();
uint8_t oled_spi_transfer(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_OLED_SPI_H__ */
