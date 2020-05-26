#include "handlers.h"
#include "nts1_iface.h"
#include "text.h"
#include "debug.h"
#include "nts1_defs.h"

__IO char handler_debug_buf[32];

void nts1_handle_note_off_event(const nts1_rx_note_off_t *note_off) {
  //debug_text("!NOTE:OFF", 9);
  nts1_note_off(note_off->note);
}

void nts1_handle_note_on_event(const nts1_rx_note_on_t *note_on) {
  //debug_text("!NOTE:ON", 8);
  //nts1_note_on(note_on->note, note_on->velocity);
}

void nts1_handle_step_tick_event(void) { 
  //static uint8_t tick = 0;
  //text_0x_from_uint8(handler_debug_buf, tick);
  //debug_text(handler_debug_buf, 3);
  //++tick;
}

void nts1_handle_unit_desc_event(const nts1_rx_unit_desc_t *unit_desc) {
  //handler_debug_buf[0] = 'U';
  //handler_debug_buf[1] = 'D';
  //handler_debug_buf[2] = 'e';
  //handler_debug_buf[3] = 's';
  //handler_debug_buf[4] = 'c';
  //handler_debug_buf[5] = '\n';
  //text_0x_from_uint8(&(handler_debug_buf[6]), unit_desc->main_id);
  //handler_debug_buf[8] = ':';
  //text_0x_from_uint8(&(handler_debug_buf[9]), unit_desc->sub_id);
  //handler_debug_buf[11] = '+';
  //text_0x_from_uint8(&(handler_debug_buf[12]), unit_desc->param_count);
  //handler_debug_buf[14] = '\n';
  //for (uint8_t i=0;i<13;++i) {
  //  handler_debug_buf[i+15] = unit_desc->name[i];
  //}
  //handler_debug_buf[28] = 0;
  //debug_text(handler_debug_buf, 28);

  nts1_defs_unit_desc_handler(unit_desc);
}

void nts1_handle_edit_param_desc_event(const nts1_rx_edit_param_desc_t *param_desc) {
  handler_debug_buf[0] = 'P';
  handler_debug_buf[1] = 'D';
  handler_debug_buf[2] = 'e';
  handler_debug_buf[3] = 's';
  handler_debug_buf[4] = 'c';
  handler_debug_buf[5] = '\n';
  text_0x_from_uint8(&(handler_debug_buf[6]), param_desc->main_id);
  handler_debug_buf[8] = ':';
  text_0x_from_uint8(&(handler_debug_buf[9]), param_desc->sub_id);
  handler_debug_buf[11] = ':';
  text_0x_from_uint8(&(handler_debug_buf[12]), param_desc->value_type);
  handler_debug_buf[14] = '\n';
  text_0x_from_uint8(&(handler_debug_buf[15]), param_desc->min);
  handler_debug_buf[17] = ':';
  text_0x_from_uint8(&(handler_debug_buf[18]), param_desc->max);
  handler_debug_buf[20] = '\n';

  for (uint8_t i=0;i<11;++i) {
    handler_debug_buf[i+21] = param_desc->name[i];
  }
  debug_text(handler_debug_buf, 32);

  nts1_defs_param_desc_handler(param_desc);
}

void nts1_handle_value_event(const nts1_rx_value_t *ve) {
  //handler_debug_buf[0] = 'V';
  //handler_debug_buf[1] = 'a';
  //handler_debug_buf[2] = 'l';
  //handler_debug_buf[3] = 'u';
  //handler_debug_buf[4] = 'e';
  //handler_debug_buf[5] = '\n';
  //text_0x_from_uint8(&(handler_debug_buf[6]), ve->req_id);
  //handler_debug_buf[8] = ':';
  //text_0x_from_uint8(&(handler_debug_buf[9]), ve->main_id);
  //handler_debug_buf[11] = ':';
  //text_0x_from_uint8(&(handler_debug_buf[12]), ve->sub_id);
  //handler_debug_buf[14] = '\n';

  //// NOTE: 最適化オプションが -Os だとtext_0x_from_uint16呼び出し内の8bit右シフトでフリーズしてしまう
  ////       -Os や -Og だと問題ないので、何かしら最適化の問題がある。
  //text_0x_from_uint16(&(handler_debug_buf[15]), ve->value);
  ////text_0x_from_uint8(&(handler_debug_buf[15]), ve->value);

  //debug_text(handler_debug_buf, 20);

  nts1_defs_param_value_handler(ve);
}

void nts1_handle_param_change(const nts1_rx_param_change_t *param_change) {
  //handler_debug_buf[0] = 'P';
  //handler_debug_buf[1] = 'C';
  //handler_debug_buf[2] = 'h';
  //handler_debug_buf[3] = 'a';
  //handler_debug_buf[4] = 'n';
  //handler_debug_buf[5] = 'g';
  //handler_debug_buf[6] = 'e';
  //handler_debug_buf[7] = '!';
  //handler_debug_buf[8] = '\n';
  //text_0x_from_uint8(&(handler_debug_buf[9]), param_change->param_id);
  //handler_debug_buf[11] = ':';
  //text_0x_from_uint8(&(handler_debug_buf[12]), param_change->param_subid);
  //handler_debug_buf[13] = '\n';
  //text_0x_from_uint8(&(handler_debug_buf[14]), param_change->msb);
  //handler_debug_buf[16] = ':';
  //text_0x_from_uint8(&(handler_debug_buf[17]), param_change->lsb);
  //debug_text(handler_debug_buf, 20);
}
