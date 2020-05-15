#include "button.h"
#include "stm32f0xx_ll_gpio.h"

typedef struct {
  uint8_t index;
  uint8_t pin;
} ButtonConfigSingle;

typedef struct {
  uint8_t start_index;
  uint8_t row_size;
  uint8_t col_size;
  uint8_t row_pins[16];
  uint8_t col_pins[16];
} ButtonConfigMatrix;

#define BUTTON_STATE_SIZE 256
#define BUTTON_CONFIG_SINGLE_SIZE (256/8)
#define BUTTON_CONFIG_MATRIX_SIZE 8

__IO uint8_t button_state[BUTTON_STATE_SIZE] = {0};
__IO uint8_t button_state_history[BUTTON_STATE_SIZE] = {0};
__IO uint8_t button_config_single_size = 0;
__IO ButtonConfigSingle button_config_single[BUTTON_CONFIG_SINGLE_SIZE];
__IO uint8_t button_config_matrix_size = 0;
__IO ButtonConfigMatrix button_config_matrix[BUTTON_CONFIG_MATRIX_SIZE];
__IO uint8_t button_matrix_proc_idx[BUTTON_CONFIG_MATRIX_SIZE];

FORCE_INLINE void button_gpio_pin_init(uint8_t pin, uint8_t out_flag) {
  LL_GPIO_InitTypeDef gpio;
  if (out_flag) {
    gpio.Mode = LL_GPIO_MODE_OUTPUT;
    gpio.Pull = LL_GPIO_PULL_NO;
  } else {
    gpio.Mode = LL_GPIO_MODE_INPUT;
    gpio.Pull = LL_GPIO_PULL_NO;
  }
  gpio.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  gpio.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  gpio.Pin = get_gpio_pin_bits(pin);
  LL_GPIO_Init(get_gpio_typedef(pin), &gpio);
}

void button_register_single(uint8_t index, uint8_t pin) {
  ButtonConfigSingle config = {index, pin};
  button_config_single[button_config_single_size] = config;
  ++button_config_single_size;

  LL_GPIO_InitTypeDef gpio;
  gpio.Mode = LL_GPIO_MODE_INPUT;
  gpio.Pull = LL_GPIO_PULL_UP;
  gpio.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  gpio.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  gpio.Pin = get_gpio_pin_bits(pin);
  LL_GPIO_Init(get_gpio_typedef(pin), &gpio);
}

uint8_t button_register_matrix(uint8_t start_index, uint8_t row_size, uint8_t col_size) {
  uint8_t idx = button_config_matrix_size;
  button_config_matrix[idx].start_index = start_index;
  button_config_matrix[idx].row_size = row_size;
  button_config_matrix[idx].col_size = col_size;
  button_matrix_proc_idx[idx] = 0;
  ++button_config_matrix_size;
  return idx;
}

void button_register_matrix_row_pin(uint8_t matrix_idx, uint8_t row_idx, uint8_t pin) {
  button_config_matrix[matrix_idx].row_pins[row_idx] = pin;
  button_gpio_pin_init(pin, 1);
}

void button_register_matrix_col_pin(uint8_t matrix_idx, uint8_t col_idx, uint8_t pin) {
  button_config_matrix[matrix_idx].col_pins[col_idx] = pin;
  button_gpio_pin_init(pin, 0);
}

void button_unregister() {
  button_config_single_size = 0;
  button_config_matrix_size = 0;
}

void button_setup() {
/*  for (uint8_t i=0;i<button_config_matrix_size;++i) {*/
/*    ButtonConfigMatrix config = button_config_matrix[i];*/
/*    for (uint8_t j=0;j<config.row_size;++j) {*/
/*      gpio_write(config.row_pins[j], 0);*/
/*    }*/
/*  }*/
}

void button_event_callback_null(uint8_t button_idx, uint8_t on) {}
static ButtonEventCallback button_event_callback = button_event_callback_null;
void button_event_listen(ButtonEventCallback cb) {
  button_event_callback = cb;
}

void button_process() {
  for (uint8_t i=0;i<button_config_single_size;++i) {
    ButtonConfigSingle config = button_config_single[i];
    uint8_t before_on = (button_state_history[config.index] == 0xFF);
    uint8_t before_off = (button_state_history[config.index] == 0x00);
    button_state_history[config.index] <<= 1;
    button_state_history[config.index] |= (!gpio_read(config.pin) ? 1 : 0);
    uint8_t on = (button_state_history[config.index] == 0xFF);
    uint8_t off = (button_state_history[config.index] == 0x00);
    if (before_on != on) {
      button_state[config.index] = 1;
      button_event_callback(config.index, 1);
    } else if (before_off != off) {
      button_state[config.index] = 0;
      button_event_callback(config.index, 0);
    }
  }

  for (uint8_t i=0;i<button_config_matrix_size;++i) {
    ButtonConfigMatrix config = button_config_matrix[i];
    uint8_t row_idx = button_matrix_proc_idx[i];
    int8_t row_pin = config.row_pins[row_idx];
    gpio_write(row_pin, 1);
    for (uint8_t j=0;j<config.col_size;++j) {
      uint8_t index = config.start_index + (row_idx * config.col_size) + j;
      uint8_t before_on = (button_state_history[index] == 0xFF);
      uint8_t before_off = (button_state_history[index] == 0x00);
      int8_t col_pin = config.col_pins[j];
      button_state_history[index] <<= 1;
      button_state_history[index] |= (gpio_read(col_pin) ? 1 : 0);
      uint8_t on = (button_state_history[index] == 0xFF);
      uint8_t off = (button_state_history[index] == 0x00);
      if (before_on != on) {
        button_state[index] = 1;
        button_event_callback(index, 1);
      } else if (before_off != off) {
        button_state[index] = 0;
        button_event_callback(index, 0);
      }
    }
    gpio_write(row_pin, 0);
    button_matrix_proc_idx[i] = (button_matrix_proc_idx[i] + 1) % config.row_size;
    gpio_write(config.row_pins[button_matrix_proc_idx[i]], 1);
  }
}
