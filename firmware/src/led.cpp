#include "main.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_def.h"
#include "stm32f0xx_hal_spi.h"
#include "stm32_def.h"
#include "PeripheralPins.h"
#include "PinAF_STM32F1.h"
#include "pinconfig.h"
#include "led.h"

#define GPIO_LED_PORT GPIOC
#define GPIO_LED_A GPIO_PIN_8
#define GPIO_LED_B GPIO_PIN_9
#define GPIO_LED_C GPIO_PIN_10
#define GPIO_LED_D GPIO_PIN_11
#define GPIO_LED_1 GPIO_PIN_12
#define GPIO_LED_2 GPIO_PIN_13
#define GPIO_LED_3 GPIO_PIN_14
#define GPIO_LED_4 GPIO_PIN_15
#define GPIO_LED_RUN GPIO_PIN_0

#define GPIO_LED_MODE GPIO_PIN_12

void led_setup() {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_LED_RUN | GPIO_LED_A | GPIO_LED_B | GPIO_LED_C | GPIO_LED_D | GPIO_LED_1 | GPIO_LED_2 | GPIO_LED_3 | GPIO_LED_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(GPIO_LED_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_LED_MODE;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIO_LED_PORT, GPIO_LED_RUN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, GPIO_LED_MODE, GPIO_PIN_SET);
}

void led_process() {
  static uint8_t led_idx = 0;
  
  HAL_GPIO_WritePin(GPIO_LED_PORT, GPIO_LED_1, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIO_LED_PORT, GPIO_LED_2, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIO_LED_PORT, GPIO_LED_3, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIO_LED_PORT, GPIO_LED_4, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIO_LED_PORT, GPIO_LED_1 << (led_idx % 4), GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIO_LED_PORT, GPIO_LED_A << (led_idx / 4), GPIO_PIN_SET);

  led_idx = (led_idx+1) % 16;
}
