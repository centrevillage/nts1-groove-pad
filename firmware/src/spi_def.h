#ifndef __N1GP_SPI_DEF_H__
#define __N1GP_SPI_DEF_H__

#include "main.h"
#include "stm32f0xx_ll_spi.h"
#include "stm32f0xx_ll_bus.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
 SPI_TypeDef *p_spi;
} SpiDef;

#include "spi_def_stm32f072.h"

static inline SpiDef spi_def_get(uint8_t idx) {
  return spi_defs[idx]; 
}

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_SPI_DEF_H__ */
