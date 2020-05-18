#ifndef __N1GP_OLED_SPI_H__
#define __N1GP_OLED_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void oled_spi_setup();
uint8_t oled_spi_transfer(uint8_t data);
uint8_t oled_spi_is_busy();

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_OLED_SPI_H__ */
