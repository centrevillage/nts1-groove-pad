#include "main.h"
#include "stm32f0xx_ll_gpio.h"
#include "led.h"

#define GPIO_LED_PORT GPIOC
#define GPIO_LED_A LL_GPIO_PIN_8
#define GPIO_LED_B LL_GPIO_PIN_9
#define GPIO_LED_C LL_GPIO_PIN_10
#define GPIO_LED_D LL_GPIO_PIN_11
#define GPIO_LED_1 LL_GPIO_PIN_12
#define GPIO_LED_2 LL_GPIO_PIN_13
#define GPIO_LED_3 LL_GPIO_PIN_14
#define GPIO_LED_4 LL_GPIO_PIN_15
#define GPIO_LED_RUN LL_GPIO_PIN_0

#define GPIO_LED_MODE LL_GPIO_PIN_12

__IO uint32_t led_bits = 0;

void led_setup() {
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = GPIO_LED_RUN | GPIO_LED_A | GPIO_LED_B | GPIO_LED_C | GPIO_LED_D | GPIO_LED_1 | GPIO_LED_2 | GPIO_LED_3 | GPIO_LED_4;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIO_LED_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_LED_MODE;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static const uint8_t led_row_pins[] = {
  PIN_C8, PIN_C9, PIN_C10, PIN_C11
};

static const uint8_t led_col_pins[] = {
  PIN_C12, PIN_C13, PIN_C14, PIN_C15
};

void led_process() {
  static uint8_t led_matrix_idx = 0;
  gpio_write(led_row_pins[(led_matrix_idx+3)%4], 0);

  gpio_write(PIN_A12, !!(led_bits & (1UL<<16)));//MODE
  gpio_write(PIN_C0, !!(led_bits & (1UL<<17)));//RUN

  for (uint8_t i=0;i<4;++i) {
    gpio_write(led_col_pins[i], !(led_bits & (1UL << (led_matrix_idx*4+i))));
  }
  gpio_write(led_row_pins[led_matrix_idx], 1);

  led_matrix_idx = (led_matrix_idx+1) % 4;
}

void led_set(uint8_t index, uint8_t on) {
  if (on) {
    led_bits |= (1UL<<index);
  } else {
    led_bits &= ~(1UL<<index);
  }
};

void led_clear() {
  led_bits = 0;
}
