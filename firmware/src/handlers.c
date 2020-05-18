#include "handlers.h"
#include "nts1_iface.h"
#include "text.h"
#include "debug.h"

static char handler_debug_buf[24];

void nts1_handle_note_off_event(const nts1_rx_note_off_t *note_off) {
  debug_text("!NOTE:OFF", 9);
  nts1_note_off(note_off->note);
}

void nts1_handle_note_on_event(const nts1_rx_note_on_t *note_on) {
  debug_text("!NOTE:ON", 8);
  //nts1_note_on(note_on->note, note_on->velocity);
}

void nts1_handle_step_tick_event(void) { 
  //static uint8_t tick = 0;
  //text_0x_from_uint8(handler_debug_buf, tick);
  //debug_text(handler_debug_buf, 3);
  //++tick;
}

void nts1_handle_unit_desc_event(const nts1_rx_unit_desc_t *unit_desc) {
  debug_text("!UNIT", 5);
  //handler_debug_buf[0] = 'U';
  //handler_debug_buf[1] = '!';
  //for (uint8_t i=0;i<13;++i) {
  //  handler_debug_buf[i+2] = unit_desc->name[i];
  //}
  //handler_debug_buf[15] = 0;
  //debug_text(handler_debug_buf, 16);
}

void nts1_handle_edit_param_desc_event(const nts1_rx_edit_param_desc_t *param_desc) {
  debug_text("!PARAM", 6);
  //handler_debug_buf[0] = 'P';
  //handler_debug_buf[1] = '!';
  //for (uint8_t i=0;i<13;++i) {
  //  handler_debug_buf[i+2] = param_desc->name[i];
  //}
  //handler_debug_buf[15] = 0;
  //debug_text(handler_debug_buf, 16);
}

void nts1_handle_value_event(const nts1_rx_value_t *value) {
  debug_text("!VALUE", 6);
  //handler_debug_buf[0] = 'V';
  //handler_debug_buf[1] = '!';
  //text_0x_from_uint16(&(handler_debug_buf[2]), value->value);
  //handler_debug_buf[6] = 0;
  //debug_text(handler_debug_buf, 7);
}

void nts1_handle_param_change(const nts1_rx_param_change_t *param_change) {
  debug_text("!PCHNG", 6);
  //handler_debug_buf[0] = 'C';
  //handler_debug_buf[1] = '!';
  //text_0x_from_uint8(&(handler_debug_buf[2]), param_change->msb);
  //text_0x_from_uint8(&(handler_debug_buf[4]), param_change->lsb);
  //handler_debug_buf[6] = 0;
  //debug_text(handler_debug_buf, 7);
}
