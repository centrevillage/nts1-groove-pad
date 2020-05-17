#ifndef __N1GP_HANDLERS_H__
#define __N1GP_HANDLERS_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void nts1_handle_note_off_event(const nts1_rx_note_off_t *note_off);
void nts1_handle_note_on_event(const nts1_rx_note_on_t *note_on);
void nts1_handle_step_tick_event(void);
void nts1_handle_unit_desc_event(const nts1_rx_unit_desc_t *unit_desc);
void nts1_handle_edit_param_desc_event(const nts1_rx_edit_param_desc_t *param_desc);
void nts1_handle_value_event(const nts1_rx_value_t *value);
void nts1_handle_param_change(const nts1_rx_param_change_t *param_change);

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_HANDLERS_H__ */
