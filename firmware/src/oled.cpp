#include "systick_timer.h"
#include "oled.h"
#include "input.h"
#include "screen_conf.h"
#include "draw.h"
#include "text.h"
#include "debug.h"
#include "screen.h"

#include <igb_stm32/periph/rcc.hpp>
#include <igb_stm32/periph/spi.hpp>

using namespace igb_stm32;

static uint8_t oled_buffer[SCREEN_WIDTH * SCREEN_HEIGHT / 8];
static uint8_t oled_cursor_x = 0;
static uint8_t oled_cursor_y = 0;

void oled_init();
void oled_reset();
void oled_send_command(uint8_t byte);
void oled_send_data(uint8_t* buffer, size_t buff_size);
void oled_draw_fill_bg();
void oled_draw_fill_fg();
void oled_set_cursor(uint8_t x, uint8_t y);
void oled_draw_pixel(uint8_t x, uint8_t y, uint8_t fg);
void oled_update_screen();

auto oled_cs_pin = GpioPin::newPin(GpioPinType::pb9);
auto oled_dc_pin = GpioPin::newPin(GpioPinType::pb5);
auto oled_reset_pin = GpioPin::newPin(GpioPinType::pb8);
auto oled_spi = Spi::newSpi(SpiType::spi1);

void oled_gpio_setup() {
  GpioPort port_b { GpioType::gpiob };
  port_b.enable();

  oled_cs_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
  oled_dc_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
  oled_reset_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
}

void oled_init() {
  oled_reset();
  delay_msec(100);

  oled_send_command(0xAE); // display off
  oled_send_command(0x20); // Set Memory Addressing Mode
  oled_send_command(0x00); // 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode;
                           // 10b,Page Addressing Mode (RESET); 11b,Invalid
  oled_send_command(0xB0); // Set Page Start Address for Page Addressing Mode,0-7
  oled_send_command(0xC8); // Set COM Output Scan Direction
  oled_send_command(0x00); // Set low column address
  oled_send_command(0x10); // Set high column address
  oled_send_command(0x40); // Set start line address - CHECK
  oled_send_command(0x81); // Set contrast control register - CHECK
  oled_send_command(0xFF);
  oled_send_command(0xA1); // Set segment re-map 0 to 127 - CHECK
  oled_send_command(0xA6); // Set normal color
  //oled_send_command(0xA7); // Set invert color
  oled_send_command(0xA8); // Set multiplex ratio(1 to 64) - CHECK
  oled_send_command(0x3F); //
  oled_send_command(0xA4); // 0xa4,Output follows RAM content;0xa5,Output ignores RAM content
  oled_send_command(0xD3); // Set display offset - CHECK
  oled_send_command(0x00); // Not offset
  oled_send_command(0xD5); // Set display clock divide ratio/oscillator frequency
  //oled_send_command(0xF0); // Set divide ratio
  oled_send_command(0x80); // Set divide ratio
  oled_send_command(0xD9); // Set pre-charge period
  //oled_send_command(0x22); //
  oled_send_command(0xF1); //
  oled_send_command(0xDA); // Set com pins hardware configuration - CHECK
  oled_send_command(0x12);
  oled_send_command(0xDB); // Set vcomh
  oled_send_command(0x20); // 0x20,0.77xVcc
  oled_send_command(0x8D); // Set DC-DC enable
  oled_send_command(0x14); //
  oled_send_command(0x2E); // stop scroll
  oled_send_command(0xAF); // turn on SSD1306 panel
}

void oled_reset() {
  oled_cs_pin.high();
  oled_reset_pin.high();
  delay_msec(1);
  oled_reset_pin.low();
  delay_msec(10);
  oled_reset_pin.high();
  delay_msec(10);
}

void oled_draw_fill_bg() {
  for (size_t i = 0; i < sizeof(oled_buffer); ++i) {
    oled_buffer[i] = 0;
  }
}
void oled_draw_fill_fg() {
  for (size_t i = 0; i < sizeof(oled_buffer); ++i) {
    oled_buffer[i] = 0xFF;
  }
}
void oled_set_cursor(uint8_t x, uint8_t y) {
  oled_cursor_x = x;
  oled_cursor_y = y;
}
void oled_draw_pixel(uint8_t x, uint8_t y, uint8_t fg) {
  if (fg) {
    oled_buffer[x + (y / 8) * SCREEN_WIDTH] |= 1 << (y % 8);
  } else {
    oled_buffer[x + (y / 8) * SCREEN_WIDTH] &= ~(1 << (y % 8));
  }
}
void oled_update_screen() {
  for (uint8_t i = 0; i < SCREEN_HEIGHT/8; ++i) {
    oled_send_command(0xB0 + i); // Set the current RAM page address.
    oled_send_command(0x00);
    oled_send_command(0x10);
    oled_send_data(&oled_buffer[SCREEN_WIDTH*i], SCREEN_WIDTH);
  }
}

void oled_send_command(uint8_t byte) {
  oled_cs_pin.low(); // select OLED
  oled_dc_pin.low(); // command
  oled_spi.transferU8sync(byte);
  oled_cs_pin.high(); // un-select OLED
}

void oled_send_data(uint8_t* buffer, size_t buff_size) {
  oled_cs_pin.low(); // select OLED
  oled_dc_pin.high(); // data
  oled_spi.transferU8sync(0);
  oled_spi.transferU8sync(0);
  for (size_t i = 0; i < buff_size; ++i) {
    oled_spi.transferU8sync(buffer[i]);
  }
  oled_cs_pin.high(); // un-select OLED
}

void oled_setup() {
  Spi::prepareSpiMaster(SpiType::spi1, GpioPinType::pa7, GpioPinType::pa6, GpioPinType::pa5, SpiBaudratePrescaler::DIV2);

  oled_gpio_setup();
  oled_init();
}

static char oled_text_buffer[32] = {0};
static uint8_t oled_text_buffer_len = 0;

void oled_process() {
  screen_draw(oled_buffer);
  oled_update_screen();
}
