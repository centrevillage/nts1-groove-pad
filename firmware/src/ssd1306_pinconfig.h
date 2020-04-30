#ifndef __SSD1306_PINCONFIG_H__
#define __SSD1306_PINCONFIG_H__

//#define SCREEN_WIDTH  128
#define SCREEN_WIDTH  130
#define SCREEN_HEIGHT 64

#define SSD1306_CS_Port         GPIOB
#define SSD1306_CS_Pin          LL_GPIO_PIN_9
#define SSD1306_DC_Port         GPIOB
#define SSD1306_DC_Pin          LL_GPIO_PIN_5
#define SSD1306_Reset_Port      GPIOB
#define SSD1306_Reset_Pin       LL_GPIO_PIN_8
#define SSD1306_HEIGHT          SCREEN_HEIGHT
#define SSD1306_WIDTH           SCREEN_WIDTH
#define SSD1306_USE_SPI         1

#endif /* __SSD1306_PINCONFIG_H__ */