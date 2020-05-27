#include "nts1_iface.h"
#include "nts1_defs.h"
#include "state.h"
#include "timer.h"
#include "debug.h"

volatile OscDef osc_defs[OSC_DEFS_SIZE];
volatile FilterDef filter_defs[FILTER_DEFS_SIZE];
volatile AmpEgDef ampeg_defs[AMPEG_DEFS_SIZE];
volatile ModFxDef modfx_defs[MODFX_DEFS_SIZE];
volatile DelFxDef delfx_defs[DELFX_DEFS_SIZE];
volatile RevFxDef revfx_defs[REVFX_DEFS_SIZE];
volatile ArpPatDef arppat_defs[ARPPAT_DEFS_SIZE];
volatile ArpIntervalsDef arpint_defs[ARPINT_DEFS_SIZE];
volatile uint8_t osc_defs_size = 0;
volatile uint8_t filter_defs_size;
volatile uint8_t ampeg_defs_size;
volatile uint8_t modfx_defs_size = 0;
volatile uint8_t delfx_defs_size = 0;
volatile uint8_t revfx_defs_size = 0;
volatile uint8_t arppat_defs_size;
volatile uint8_t arpint_defs_size;

typedef enum {
  NTS1_DEF_LOAD_PHASE_INIT = 0,
  NTS1_DEF_LOAD_PHASE_COUNT,
  NTS1_DEF_LOAD_PHASE_OSC_DESC,
  NTS1_DEF_LOAD_PHASE_FILTER_DESC,
  NTS1_DEF_LOAD_PHASE_AMPEG_DESC,
  NTS1_DEF_LOAD_PHASE_MODFX_DESC,
  NTS1_DEF_LOAD_PHASE_DELFX_DESC,
  NTS1_DEF_LOAD_PHASE_REVFX_DESC,
  NTS1_DEF_LOAD_PHASE_ARPPAT_DESC,
  NTS1_DEF_LOAD_PHASE_ARPINT_DESC,
  NTS1_DEF_LOAD_PHASE_OSC1_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC2_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC3_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC4_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC5_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC6_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC7_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC8_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC9_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC10_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC11_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC12_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC13_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC14_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC15_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC16_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC17_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC18_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC19_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC20_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC21_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC22_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC23_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC24_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC25_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC26_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC27_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC28_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC29_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC30_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC31_PARAM,
  NTS1_DEF_LOAD_PHASE_OSC32_PARAM,
  NTS1_DEF_LOAD_PHASE_COMPLETE
} Nts1DefLoadPhase;

volatile Nts1DefLoadPhase _nts1_defs_lphase = NTS1_DEF_LOAD_PHASE_COMPLETE;
static volatile uint32_t _nts1_defs_load_bits = 0;
volatile uint8_t _nts1_defs_osc_param_loading_idx = 0;
volatile uint32_t _nts1_defs_phase_start_mmsec = 0;
volatile nts1_tx_event_t _nts1_defs_load_events[32];
volatile nts1_tx_event_t _nts1_defs_load_events_size;

static inline void nts1_defs_retry_phase() {
  if (_nts1_defs_lphase == NTS1_DEF_LOAD_PHASE_INIT) {
    return;
  }
  _nts1_defs_phase_start_mmsec = current_msec();
  _nts1_defs_lphase -= 1;
  _nts1_defs_load_bits = 0xFFFFFFFF;
}

static inline void nts1_defs_check_timeout() {
  if (_nts1_defs_lphase == NTS1_DEF_LOAD_PHASE_INIT) {
    return;
  }
  if (current_msec() - _nts1_defs_phase_start_mmsec > 1500) {
    nts1_defs_retry_phase();
  }
}

static inline void nts1_defs_next_phase() {
  if (_nts1_defs_lphase == NTS1_DEF_LOAD_PHASE_COMPLETE) {
    return;
  }
  _nts1_defs_phase_start_mmsec = current_msec();
  _nts1_defs_load_bits = 0;
  _nts1_defs_lphase += 1;
}

#define NTS1_DEF_COUNT_REQ_SIZE 8

static inline uint8_t _nts1_def_is_all_ok(uint32_t bits, uint32_t size) {
  uint32_t size_bits = (1<<size)-1;
  return (bits & size_bits) == size_bits;
}

static const nts1_tx_event_t nts1_defs_count_load_requests[NTS1_DEF_COUNT_REQ_SIZE] = {
  {k_nts1_tx_event_id_req_unit_count, k_param_id_osc_type, 0},
  {k_nts1_tx_event_id_req_unit_count, k_param_id_filt_type, 0},
  {k_nts1_tx_event_id_req_unit_count, k_param_id_ampeg_type, 0},
  {k_nts1_tx_event_id_req_unit_count, k_param_id_mod_type, 0},
  {k_nts1_tx_event_id_req_unit_count, k_param_id_del_type, 0},
  {k_nts1_tx_event_id_req_unit_count, k_param_id_rev_type, 0},
  {k_nts1_tx_event_id_req_unit_count, k_param_id_arp_pattern, 0},
  {k_nts1_tx_event_id_req_unit_count, k_param_id_arp_intervals, 0},
};


void nts1_defs_req_load() {
  if (_nts1_defs_lphase == NTS1_DEF_LOAD_PHASE_COMPLETE) {
    _nts1_defs_phase_start_mmsec = current_msec();
    _nts1_defs_lphase = NTS1_DEF_LOAD_PHASE_INIT;
  }
}

void nts1_defs_process_loading() {
  if (_nts1_defs_lphase == NTS1_DEF_LOAD_PHASE_COMPLETE) { return; }

  nts1_defs_check_timeout();

  switch (_nts1_defs_lphase) {
    case NTS1_DEF_LOAD_PHASE_INIT:
      debug_text("INIT", 4);

      nts1_defs_next_phase();
      while (nts1_send_events(nts1_defs_count_load_requests, NTS1_DEF_COUNT_REQ_SIZE) != k_nts1_status_ok);
      _nts1_defs_phase_start_mmsec = current_msec();
      break;
    case NTS1_DEF_LOAD_PHASE_COUNT:
      debug_text("COUNT", 5);

      if (_nts1_def_is_all_ok(_nts1_defs_load_bits, NTS1_DEF_COUNT_REQ_SIZE)) {
        nts1_defs_next_phase();
        for (uint8_t i=0;i<osc_defs_size;++i) {
          while (nts1_req_osc_desc(i) != k_nts1_status_ok);
          _nts1_defs_phase_start_mmsec = current_msec();
        }
      }
      break;
    case NTS1_DEF_LOAD_PHASE_OSC_DESC:
      debug_text("OSC_DESC", 8);

      if (_nts1_def_is_all_ok(_nts1_defs_load_bits, osc_defs_size)) {
        nts1_defs_next_phase();
        for (uint8_t i=0;i<filter_defs_size;++i) {
          while (nts1_req_filt_desc(i) != k_nts1_status_ok);
          _nts1_defs_phase_start_mmsec = current_msec();
        }
      }
      break;
    case NTS1_DEF_LOAD_PHASE_FILTER_DESC:
      debug_text("FILT_DESC", 9);

      if (_nts1_def_is_all_ok(_nts1_defs_load_bits, filter_defs_size)) {
        nts1_defs_next_phase();
        for (uint8_t i=0;i<ampeg_defs_size;++i) {
          while (nts1_req_ampeg_desc(i) != k_nts1_status_ok);
          _nts1_defs_phase_start_mmsec = current_msec();
        }
      }
      break;
    case NTS1_DEF_LOAD_PHASE_AMPEG_DESC:
      debug_text("EG_DESC", 7);

      if (_nts1_def_is_all_ok(_nts1_defs_load_bits, ampeg_defs_size)) {
        nts1_defs_next_phase();
        for (uint8_t i=0;i<modfx_defs_size;++i) {
          while (nts1_req_mod_desc(i) != k_nts1_status_ok);
          _nts1_defs_phase_start_mmsec = current_msec();
        }
      }
      break;
    case NTS1_DEF_LOAD_PHASE_MODFX_DESC:
      debug_text("MODFX_DESC", 10);

      if (_nts1_def_is_all_ok(_nts1_defs_load_bits, modfx_defs_size)) {
        nts1_defs_next_phase();
        for (uint8_t i=0;i<delfx_defs_size;++i) {
          while (nts1_req_del_desc(i) != k_nts1_status_ok);
          _nts1_defs_phase_start_mmsec = current_msec();
        }
      }
      break;
    case NTS1_DEF_LOAD_PHASE_DELFX_DESC:
      debug_text("DELFX_DESC", 10);

      if (_nts1_def_is_all_ok(_nts1_defs_load_bits, delfx_defs_size)) {
        nts1_defs_next_phase();
        for (uint8_t i=0;i<revfx_defs_size;++i) {
          while (nts1_req_rev_desc(i) != k_nts1_status_ok);
          _nts1_defs_phase_start_mmsec = current_msec();
        }
      }
      break;
    case NTS1_DEF_LOAD_PHASE_REVFX_DESC:
      debug_text("REVFX_DESC", 10);

      if (_nts1_def_is_all_ok(_nts1_defs_load_bits, revfx_defs_size)) {
        nts1_defs_next_phase();
        for (uint8_t i=0;i<arppat_defs_size;++i) {
          while (nts1_req_arp_pattern_desc(i) != k_nts1_status_ok);
          _nts1_defs_phase_start_mmsec = current_msec();
        }
      }
      break;
    case NTS1_DEF_LOAD_PHASE_ARPPAT_DESC:
      debug_text("ARPPAT_DESC", 11);

      if (_nts1_def_is_all_ok(_nts1_defs_load_bits, arppat_defs_size)) {
        nts1_defs_next_phase();
        for (uint8_t i=0;i<arpint_defs_size;++i) {
          while (nts1_req_arp_intervals_desc(i) != k_nts1_status_ok);
          _nts1_defs_phase_start_mmsec = current_msec();
        }
      }
      break;
    case NTS1_DEF_LOAD_PHASE_ARPINT_DESC:
      debug_text("ARPINT_DESC", 11);

      if (_nts1_def_is_all_ok(_nts1_defs_load_bits, arpint_defs_size)) {
        if (osc_defs_size > 0) {
          nts1_defs_next_phase();
          debug_text("PARAM1", 6);
          if (osc_defs[0].param_count > 0) {
            while (nts1_param_change(k_param_id_osc_type, 0, 0) != k_nts1_status_ok);
            _nts1_defs_phase_start_mmsec = current_msec();
            for (uint8_t i=0; i < osc_defs[0].param_count; ++i) {
              while (nts1_req_osc_edit_param_desc(i) != k_nts1_status_ok);
              _nts1_defs_phase_start_mmsec = current_msec();
            }
          }
        } else {
          while (nts1_param_change(k_param_id_osc_type, 0, 0) != k_nts1_status_ok);
          _nts1_defs_lphase = NTS1_DEF_LOAD_PHASE_COMPLETE;
        }
      }
      break;
    case NTS1_DEF_LOAD_PHASE_OSC32_PARAM:
      debug_text("PARAM32", 7);

      if (osc_defs_size < 32) {
        while (nts1_param_change(k_param_id_osc_type, 0, 0) != k_nts1_status_ok);
        _nts1_defs_lphase = NTS1_DEF_LOAD_PHASE_COMPLETE;
        debug_text("COMPLETE", 8);
      } else if (_nts1_def_is_all_ok(_nts1_defs_load_bits, osc_defs[31].param_count)) {
        while (nts1_param_change(k_param_id_osc_type, 0, 0) != k_nts1_status_ok);
        nts1_defs_next_phase();
        debug_text("COMPLETE", 8);
      }
      break;
    default:
      if (NTS1_DEF_LOAD_PHASE_OSC1_PARAM <= _nts1_defs_lphase && _nts1_defs_lphase < NTS1_DEF_LOAD_PHASE_OSC32_PARAM) {
        //if (_nts1_defs_load_bits) {
        //  _nts1_defs_phase_start_mmsec = current_msec();
        //  char tmp[8];
        //  text_from_uint32(tmp, _nts1_defs_load_bits);
        //  debug_text(tmp, 8);
        //}
        uint8_t osc_defs_idx = _nts1_defs_lphase - NTS1_DEF_LOAD_PHASE_OSC1_PARAM;
        if (osc_defs_size <= osc_defs_idx) {
          while (nts1_param_change(k_param_id_osc_type, 0, 0) != k_nts1_status_ok);
          _nts1_defs_lphase = NTS1_DEF_LOAD_PHASE_COMPLETE;
          debug_text("COMPLETE", 8);
        } else if (_nts1_def_is_all_ok(_nts1_defs_load_bits, osc_defs[osc_defs_idx].param_count)) {
          nts1_defs_next_phase();
          osc_defs_idx = _nts1_defs_lphase - NTS1_DEF_LOAD_PHASE_OSC1_PARAM;
          if (osc_defs[osc_defs_idx].param_count > 0) {
            while (nts1_param_change(k_param_id_osc_type, 0, osc_defs_idx) != k_nts1_status_ok);
            _nts1_defs_phase_start_mmsec = current_msec();
            for (uint8_t i=0; i < osc_defs[osc_defs_idx].param_count; ++i) {
              while (nts1_req_osc_edit_param_desc(i) != k_nts1_status_ok);
              _nts1_defs_phase_start_mmsec = current_msec();
            }
          }
        }
      }
      break;
  }
}

uint8_t nts1_defs_is_complete_loading() {
  return _nts1_defs_lphase == NTS1_DEF_LOAD_PHASE_COMPLETE;
}

static inline void _nts1_defs_set_desc_name(char* dest_name, char* src_name) {
  uint8_t i=0;
  for (;i<(PARAM_NAME_LEN-1) && src_name[i] != 0;++i) {
    dest_name[i] = src_name[i];
  }
  dest_name[i] = 0;
}

void nts1_defs_unit_desc_handler(const nts1_rx_unit_desc_t* unit_desc) {
  if (NTS1_DEF_LOAD_PHASE_OSC_DESC <= _nts1_defs_lphase && _nts1_defs_lphase <= NTS1_DEF_LOAD_PHASE_ARPINT_DESC) {
    switch(_nts1_defs_lphase) {
      case NTS1_DEF_LOAD_PHASE_OSC_DESC:
        if (unit_desc->main_id == k_param_id_osc_type) {
          uint8_t idx = unit_desc->sub_id;
          osc_defs[idx].param_count = unit_desc->param_count;
          _nts1_defs_set_desc_name(osc_defs[idx].name, unit_desc->name);
          _nts1_defs_load_bits |= (1<<idx);
        }
        break;
      case NTS1_DEF_LOAD_PHASE_FILTER_DESC:
        if (unit_desc->main_id == k_param_id_filt_type) {
          uint8_t idx = unit_desc->sub_id;
          _nts1_defs_set_desc_name(filter_defs[idx].name, unit_desc->name);
          _nts1_defs_load_bits |= (1<<idx);
        }
        break;
      case NTS1_DEF_LOAD_PHASE_AMPEG_DESC:
        if (unit_desc->main_id == k_param_id_ampeg_type) {
          uint8_t idx = unit_desc->sub_id;
          _nts1_defs_set_desc_name(ampeg_defs[idx].name, unit_desc->name);
          _nts1_defs_load_bits |= (1<<idx);
        }
        break;
      case NTS1_DEF_LOAD_PHASE_MODFX_DESC:
        if (unit_desc->main_id == k_param_id_mod_type) {
          uint8_t idx = unit_desc->sub_id;
          _nts1_defs_set_desc_name(modfx_defs[idx].name, unit_desc->name);
          _nts1_defs_load_bits |= (1<<idx);
        }
        break;
      case NTS1_DEF_LOAD_PHASE_DELFX_DESC:
        if (unit_desc->main_id == k_param_id_del_type) {
          uint8_t idx = unit_desc->sub_id;
          _nts1_defs_set_desc_name(delfx_defs[idx].name, unit_desc->name);
          _nts1_defs_load_bits |= (1<<idx);
        }
        break;
      case NTS1_DEF_LOAD_PHASE_REVFX_DESC:
        if (unit_desc->main_id == k_param_id_rev_type) {
          uint8_t idx = unit_desc->sub_id;
          _nts1_defs_set_desc_name(revfx_defs[idx].name, unit_desc->name);
          _nts1_defs_load_bits |= (1<<idx);
        }
        break;
      case NTS1_DEF_LOAD_PHASE_ARPPAT_DESC:
        if (unit_desc->main_id == k_param_id_arp_pattern) {
          uint8_t idx = unit_desc->sub_id;
          _nts1_defs_set_desc_name(arppat_defs[idx].name, unit_desc->name);
          _nts1_defs_load_bits |= (1<<idx);
        }
        break;
      case NTS1_DEF_LOAD_PHASE_ARPINT_DESC:
        if (unit_desc->main_id == k_param_id_arp_intervals) {
          uint8_t idx = unit_desc->sub_id;
          _nts1_defs_set_desc_name(arpint_defs[idx].name, unit_desc->name);
          _nts1_defs_load_bits |= (1<<idx);
        }
        break;
      default:
        break;
    }
  }
}

void nts1_defs_param_desc_handler(const nts1_rx_edit_param_desc_t* param_desc) {
  if (param_desc->main_id == k_param_id_osc_edit) {
    if (NTS1_DEF_LOAD_PHASE_OSC1_PARAM <= _nts1_defs_lphase && _nts1_defs_lphase <= NTS1_DEF_LOAD_PHASE_OSC32_PARAM) {
      uint8_t osc_idx = _nts1_defs_lphase - NTS1_DEF_LOAD_PHASE_OSC1_PARAM;
      uint8_t param_idx = param_desc->sub_id;
      osc_defs[osc_idx].params[param_idx].value_type = param_desc->value_type;
      osc_defs[osc_idx].params[param_idx].min = param_desc->min;
      osc_defs[osc_idx].params[param_idx].max = param_desc->max;
      _nts1_defs_set_desc_name(osc_defs[osc_idx].params[param_idx].name, param_desc->name);
      _nts1_defs_load_bits |= 1 << (uint32_t)param_idx;
    }
  }
}

void nts1_defs_param_value_handler(const nts1_rx_value_t* value) {
  if (_nts1_defs_lphase == NTS1_DEF_LOAD_PHASE_COUNT) {
    uint8_t req_id = value->req_id;
    if (req_id == k_nts1_tx_event_id_req_unit_count) {
      switch (value->main_id) {
        case k_param_id_osc_type:
          osc_defs_size = value->value;
          _nts1_defs_load_bits |= 1;
          break;
        case k_param_id_filt_type:
          filter_defs_size = value->value;
          _nts1_defs_load_bits |= 1 << 1;
          break;
        case k_param_id_ampeg_type:
          ampeg_defs_size = value->value;
          _nts1_defs_load_bits |= 1 << 2;
          break;
        case k_param_id_mod_type:
          modfx_defs_size = value->value;
          _nts1_defs_load_bits |= 1 << 3;
          break;
        case k_param_id_del_type:
          delfx_defs_size = value->value;
          _nts1_defs_load_bits |= 1 << 4;
          break;
        case k_param_id_rev_type:
          revfx_defs_size = value->value;
          _nts1_defs_load_bits |= 1 << 5;
          break;
        case k_param_id_arp_pattern:
          arppat_defs_size = value->value;
          _nts1_defs_load_bits |= 1 << 6;
          break;
        case k_param_id_arp_intervals:
          arpint_defs_size = value->value;
          _nts1_defs_load_bits |= 1 << 7;
          break;
        default:
          break;
      }
    }
  }
}
