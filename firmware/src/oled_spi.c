#include "oled_spi.h"

#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_spi.h"
#include "stm32f0xx_ll_bus.h"

//#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
//#define READ_BIT(REG, BIT)    ((REG) & (BIT))
//#define UNUSED(x) ((void)(x))  

#define SPI_GPIO_CLK_ENA()   do { \
                               __IO uint32_t tmpreg; \
                               RCC->AHBENR |= RCC_AHBENR_GPIOAEN;\
                               /* Delay after an RCC peripheral clock enabling */\
                               tmpreg = RCC->AHBENR & RCC_AHBENR_GPIOAEN;\
                             } while(0U)
#define SPI_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI1RST))
#define SPI_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI1RST))
#define SPI_CLK_ENABLE()     do { \
                               __IO uint32_t tmpreg; \
                               RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;\
                               /* Delay after an RCC peripheral clock enabling */\
                               tmpreg = RCC->APB2ENR & RCC_APB2ENR_SPI1EN;\
                             } while(0U)
#define SPI_CLK_DISABLE()    __HAL_RCC_SPI1_CLK_DISABLE()

#define SPI_GPIO_PORT GPIOA
#define SPI_SCK_PIN   LL_GPIO_PIN_5
#define SPI_MISO_PIN  LL_GPIO_PIN_6
#define SPI_MOSI_PIN  LL_GPIO_PIN_7
#define GPIO_SPI_AF   LL_GPIO_AF_0

void oled_spi_setup() {
  //SPI_GPIO_CLK_ENA();
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SPI1);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

  LL_GPIO_InitTypeDef gpio = {0};

  gpio.Alternate = LL_GPIO_AF_0;
  gpio.Mode = LL_GPIO_MODE_ALTERNATE;
  gpio.Pull = LL_GPIO_PULL_NO;
  gpio.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  gpio.OutputType = LL_GPIO_OUTPUT_PUSHPULL;

  gpio.Pin = SPI_SCK_PIN;
  LL_GPIO_Init(SPI_GPIO_PORT, &gpio);
  gpio.Pin = SPI_MOSI_PIN;
  LL_GPIO_Init(SPI_GPIO_PORT, &gpio);
/*  gpio.Pin = SPI_MISO_PIN;*/
/*  LL_GPIO_Init(SPI_GPIO_PORT, &gpio);*/

  SPI_FORCE_RESET();
  SPI_RELEASE_RESET();
  SPI_CLK_ENABLE();

  LL_SPI_InitTypeDef spi = {0};

  spi.TransferDirection = LL_SPI_FULL_DUPLEX;
  //spi.TransferDirection = LL_SPI_HALF_DUPLEX_TX;
  spi.Mode = LL_SPI_MODE_MASTER;
  spi.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  spi.ClockPolarity = LL_SPI_POLARITY_LOW;
  spi.ClockPhase = LL_SPI_PHASE_1EDGE;
  spi.NSS = LL_SPI_NSS_SOFT;
  spi.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;
  spi.BitOrder = LL_SPI_MSB_FIRST;
  spi.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
  spi.CRCPoly = 7;
  //spi.CRCPoly = 10;

  LL_SPI_Init(SPI1, &spi);
  LL_SPI_SetStandard(SPI1, LL_SPI_PROTOCOL_MOTOROLA);
  LL_SPI_Enable(SPI1);
  LL_SPI_EnableNSSPulseMgt(SPI1);
}

uint8_t oled_spi_transfer(uint8_t data) {
  //while (!LL_SPI_IsActiveFlag_TXE(SPI1));
  //LL_SPI_TransmitData8(SPI1, data);
  ////while (LL_SPI_IsActiveFlag_RXNE(SPI1) == RESET);
  ////return LL_SPI_ReceiveData8(SPI1);

  while (LL_SPI_IsActiveFlag_BSY(SPI1));
  if (LL_SPI_IsActiveFlag_RXNE(SPI1)) LL_SPI_ReceiveData8(SPI1); // clear read buffer
  if (!LL_SPI_IsEnabled(SPI1)) LL_SPI_Enable(SPI1);
  LL_SPI_TransmitData8(SPI1, data);
  while (!LL_SPI_IsActiveFlag_TXE(SPI1));
  uint8_t received = LL_SPI_ReceiveData8(SPI1);
  return received;
}
