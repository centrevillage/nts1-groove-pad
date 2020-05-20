#include "nts1_iface.h"
#include "nts1_defs.h"
#include "state.h"

volatile OscDef osc_defs[OSC_DEFS_SIZE];
volatile ModFxDef modfx_defs[MODFX_DEFS_SIZE];
volatile DelFxDef delfx_defs[DELFX_DEFS_SIZE];
volatile RevFxDef revfx_defs[REVFX_DEFS_SIZE];

void nts1_defs_req_load() {
}

void nts1_defs_unit_desc_handler(const nts1_rx_unit_desc_t* unit_desc) {
}

void nts1_defs_param_desc_handler(const nts1_rx_edit_param_desc_t* param_desc) {
}
