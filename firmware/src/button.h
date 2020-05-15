#ifndef __N1GP_BUTTON_H__
#define __N1GP_BUTTON_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ButtonEventCallback)(uint8_t button_idx, uint8_t on);

void button_register_single(uint8_t index, uint8_t pin);
uint8_t button_register_matrix(uint8_t start_index, uint8_t row_size, uint8_t col_size);
void button_register_matrix_row_pin(uint8_t matrix_idx, uint8_t row_idx, uint8_t pin);
void button_register_matrix_col_pin(uint8_t matrix_idx,uint8_t col_idx, uint8_t pin);
void button_unregister();
void button_setup();
void button_process();
void button_event_listen(ButtonEventCallback cb);

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_BUTTON_H__ */
