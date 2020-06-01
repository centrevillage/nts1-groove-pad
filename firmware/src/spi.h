#ifndef __N1GP_SPI_H__
#define __N1GP_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "stm32_pinconfig.h"

void spi_simple_setup(uint8_t spi_idx, uint8_t mosi_pin, uint8_t miso_pin, uint8_t sck_pin, uint32_t baudrate);
uint8_t spi_transmit(uint8_t spi_idx, uint8_t data);
uint8_t spi_is_busy(uint8_t spi_idx);

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_SPI_H__ */
