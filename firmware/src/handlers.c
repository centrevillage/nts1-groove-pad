#include "handlers.h"
#include "nts1_iface.h"
#include "text.h"
#include "debug.h"

void nts1_handle_note_off_event(const nts1_rx_note_off_t *note_off) {
  debug_text("!NOTE:OFF", 9);
}

void nts1_handle_note_on_event(const nts1_rx_note_on_t *note_on) {
  debug_text("!NOTE:ON", 8);
}

void nts1_handle_step_tick_event(void) { 
  //static uint8_t tick = 0;
  //char debug_buf[3];
  //text_0x_from_uint8(debug_buf, tick);
  //debug_text(debug_buf, 3);
  //debug_text("!TICK", 5);
  //++tick;
}

void nts1_handle_unit_desc_event(const nts1_rx_unit_desc_t *unit_desc) {
  static char buf[15];
  buf[0] = 'U';
  buf[1] = '!';
  for (uint8_t i=0;i<13;++i) {
    buf[i+2] = unit_desc->name[i];
  }
  debug_text(buf, 15);
}

void nts1_handle_edit_param_desc_event(const nts1_rx_edit_param_desc_t *param_desc) {
  static char buf[15];
  buf[0] = 'P';
  buf[1] = '!';
  for (uint8_t i=0;i<13;++i) {
    buf[i+2] = param_desc->name[i];
  }
  debug_text(buf, 15);
}

void nts1_handle_value_event(const nts1_rx_value_t *value) {
  static char buf[6];
  buf[0] = 'V';
  buf[1] = '!';
  text_0x_from_uint16(&(buf[2]), value->value);
  debug_text(buf, 6);
}

void nts1_handle_param_change(const nts1_rx_param_change_t *param_change) {
  static char buf[6];
  buf[0] = 'C';
  buf[1] = '!';
  text_0x_from_uint8(&(buf[2]), param_change->msb);
  text_0x_from_uint8(&(buf[4]), param_change->lsb);
  debug_text(buf, 6);
}
