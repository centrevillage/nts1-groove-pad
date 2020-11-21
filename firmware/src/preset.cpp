#include "preset.h"
#include "preset_event.h"
#include "ram.h"

#include <igb_stm32/periph/gpio.hpp>
#include "app_input.hpp"

using namespace igb::stm32;

// アドレス範囲(256Kb= 0x00000-0x3FFFF)
// プリセットを保持するアドレス
#define GLOBAL_PRESET_RAM_ADDRESS 0x0000
#define GLOBAL_PRESET_RAM_SIZE    0x0100
#define TEMP_PRESET_RAM_ADDRESS   0x0100
#define TEMP_PRESET_RAM_SIZE      0x0080
#define TEMP_SEQ_RAM_ADDRESS      0x0200
#define TEMP_SEQ_RAM_SIZE         0x2000
#define PRESET_RAM_ADDRESS        0x2200
#define PRESET_RAM_SIZE           0x0080
#define SEQ_RAM_ADDRESS           0x3000
#define SEQ_RAM_SIZE              0x2000

volatile SeqState seq_state;
volatile PresetState preset_state;
volatile GlobalState global_state;

volatile static uint8_t _preset_is_processing = 0;

#define PRESET_DATA_BUF_SIZE 256

volatile static uint8_t preset_data_buf[PRESET_DATA_BUF_SIZE];

static inline uint32_t preset_tmp_get_address() {
  return (uint32_t)TEMP_PRESET_RAM_ADDRESS;
}

static inline uint32_t preset_get_address(uint8_t preset_num) {
  return (uint32_t)PRESET_RAM_ADDRESS + (uint32_t)PRESET_RAM_SIZE * (uint32_t)preset_num;
}

static inline uint32_t global_preset_get_address(uint8_t preset_num) {
  return (uint32_t)GLOBAL_PRESET_RAM_ADDRESS + (uint32_t)GLOBAL_PRESET_RAM_SIZE * (uint32_t)preset_num;
}

static inline void preset_data_set_uint16(uint32_t i, uint16_t value) {
  preset_data_buf[i] = value & 0xFF;
  preset_data_buf[i+1] = (value >> 8) & 0xFF;
}

static inline uint16_t preset_data_get_uint16(uint32_t i) {
  return ((uint16_t)preset_data_buf[i]) | ((uint16_t)preset_data_buf[i+1] << 8);
}

void preset_load_from_buf() {
  uint32_t i = 0;
  preset_state.version = preset_data_buf[i++];

  // osc
  preset_state.osc.index = preset_data_buf[i++];
  preset_state.osc.shape = preset_data_get_uint16(i); i+=2;
  preset_state.osc.shift_shape = preset_data_get_uint16(i); i+=2;
  preset_state.osc.lfo_rate = preset_data_get_uint16(i); i+=2;
  preset_state.osc.lfo_depth = preset_data_get_uint16(i); i+=2;
  preset_state.osc.custom_index = preset_data_buf[i++];
  for (uint8_t x = 0; x < OSC_CUSTOM_VALUES_SIZE; ++x) {
    preset_state.osc.custom_values[x] = preset_data_buf[i++];
  }
  for (uint8_t x = 0; x < OSC_CUSTOM_VALUES_SIZE; ++x) {
    preset_state.osc.custom_value_types[x] = preset_data_buf[i++];
  }
  preset_state.osc.custom_value_selected_page = preset_data_buf[i++];

  // filter
  preset_state.filter.index = preset_data_buf[i++];
  preset_state.filter.cutoff = preset_data_get_uint16(i); i+=2;
  preset_state.filter.peak = preset_data_get_uint16(i); i+=2;
  preset_state.filter.lfo_rate = preset_data_get_uint16(i); i+=2;
  preset_state.filter.lfo_depth = preset_data_get_uint16(i); i+=2;
  preset_state.filter._reserved1 = preset_data_get_uint16(i); i+=2;

  // ampeg
  preset_state.ampeg.index = preset_data_buf[i++];
  preset_state.ampeg.attack = preset_data_get_uint16(i); i+=2;
  preset_state.ampeg.release = preset_data_get_uint16(i); i+=2;
  preset_state.ampeg.lfo_rate = preset_data_get_uint16(i); i+=2;
  preset_state.ampeg.lfo_depth = preset_data_get_uint16(i); i+=2;
  preset_state.ampeg._reserved1 = preset_data_get_uint16(i); i+=2;

  // modfx
  preset_state.modfx.index = preset_data_buf[i++];
  preset_state.modfx.time = preset_data_get_uint16(i); i+=2;
  preset_state.modfx.depth = preset_data_get_uint16(i); i+=2;
  preset_state.modfx._reserved1 = preset_data_get_uint16(i); i+=2;
  preset_state.modfx._reserved2 = preset_data_get_uint16(i); i+=2;
  preset_state.modfx._reserved3 = preset_data_get_uint16(i); i+=2;

  // delfx
  preset_state.delfx.index = preset_data_buf[i++];
  preset_state.delfx.time = preset_data_get_uint16(i); i+=2;
  preset_state.delfx.depth = preset_data_get_uint16(i); i+=2;
  preset_state.delfx._reserved1 = preset_data_get_uint16(i); i+=2;
  preset_state.delfx.mix = preset_data_get_uint16(i); i+=2;
  preset_state.delfx._reserved2 = preset_data_get_uint16(i); i+=2;

  // revfx
  preset_state.revfx.index = preset_data_buf[i++];
  preset_state.revfx.time = preset_data_get_uint16(i); i+=2;
  preset_state.revfx.depth = preset_data_get_uint16(i); i+=2;
  preset_state.revfx._reserved1 = preset_data_get_uint16(i); i+=2;
  preset_state.revfx.mix = preset_data_get_uint16(i); i+=2;
  preset_state.revfx._reserved2 = preset_data_get_uint16(i); i+=2;

  // arp
  preset_state.arp.index = preset_data_buf[i++];
  preset_state.arp.intervals = preset_data_buf[i++];
  preset_state.arp.length = preset_data_buf[i++];
  preset_state.arp.state = preset_data_buf[i++];
  preset_state.arp.tempo = preset_data_buf[i++];

  // lfo
  preset_state.lfo.index = preset_data_buf[i++];
  preset_state.lfo.rate = preset_data_buf[i++];
  preset_state.lfo.depth = preset_data_buf[i++];
  preset_state.lfo.bpm_sync = preset_data_buf[i++];
  preset_state.lfo._reserved1 = preset_data_buf[i++];
  preset_state.lfo._reserved2 = preset_data_buf[i++];

  // scale
  preset_state.scale.index = preset_data_buf[i++];
  preset_state.scale._reserved = preset_data_buf[i++];

  // transpose
  preset_state.transpose.offset = preset_data_buf[i++];
  preset_state.transpose._reserved = preset_data_buf[i++];

  // stutter
  preset_state.stutter.index = preset_data_buf[i++];
  preset_state.stutter._reserved = preset_data_buf[i++];

  // slide
  preset_state.slide.value = preset_data_buf[i++];
  preset_state.slide.type = preset_data_buf[i++];

  // rand
  preset_state.rand.pitch = preset_data_buf[i++];
  preset_state.rand._reserved = preset_data_buf[i++];
}

void preset_save_to_buf() {
  uint32_t i = 0;
  preset_data_buf[i++] = preset_state.version;

  // osc
  preset_data_buf[i++] = preset_state.osc.index;
  preset_data_set_uint16(i, preset_state.osc.shape); i+=2;
  preset_data_set_uint16(i, preset_state.osc.shift_shape); i+=2;
  preset_data_set_uint16(i, preset_state.osc.lfo_rate); i+=2;
  preset_data_set_uint16(i, preset_state.osc.lfo_depth); i+=2;
  preset_data_buf[i++] = preset_state.osc.custom_index;
  for (uint8_t x = 0; x < OSC_CUSTOM_VALUES_SIZE; ++x) {
    preset_data_buf[i++] = preset_state.osc.custom_values[x];
  }
  for (uint8_t x = 0; x < OSC_CUSTOM_VALUES_SIZE; ++x) {
    preset_data_buf[i++] = preset_state.osc.custom_value_types[x];
  }
  preset_data_buf[i++] = preset_state.osc.custom_value_selected_page;

  // filter
  preset_data_buf[i++] = preset_state.filter.index;
  preset_data_set_uint16(i, preset_state.filter.cutoff); i+=2;
  preset_data_set_uint16(i, preset_state.filter.peak); i+=2;
  preset_data_set_uint16(i, preset_state.filter.lfo_rate); i+=2;
  preset_data_set_uint16(i, preset_state.filter.lfo_depth); i+=2;
  preset_data_set_uint16(i, preset_state.filter._reserved1); i+=2;

  // ampeg
  preset_data_buf[i++] = preset_state.ampeg.index;
  preset_data_set_uint16(i, preset_state.ampeg.attack); i+=2;
  preset_data_set_uint16(i, preset_state.ampeg.release); i+=2;
  preset_data_set_uint16(i, preset_state.ampeg.lfo_rate); i+=2;
  preset_data_set_uint16(i, preset_state.ampeg.lfo_depth); i+=2;
  preset_data_set_uint16(i, preset_state.ampeg._reserved1); i+=2;

  // modfx
  preset_data_buf[i++] = preset_state.modfx.index;
  preset_data_set_uint16(i, preset_state.modfx.time); i+=2;
  preset_data_set_uint16(i, preset_state.modfx.depth); i+=2;
  preset_data_set_uint16(i, preset_state.modfx._reserved1); i+=2;
  preset_data_set_uint16(i, preset_state.modfx._reserved2); i+=2;
  preset_data_set_uint16(i, preset_state.modfx._reserved3); i+=2;

  // delfx
  preset_data_buf[i++] = preset_state.delfx.index;
  preset_data_set_uint16(i, preset_state.delfx.time); i+=2;
  preset_data_set_uint16(i, preset_state.delfx.depth); i+=2;
  preset_data_set_uint16(i, preset_state.delfx._reserved1); i+=2;
  preset_data_set_uint16(i, preset_state.delfx.mix); i+=2;
  preset_data_set_uint16(i, preset_state.delfx._reserved2); i+=2;

  // revfx
  preset_data_buf[i++] = preset_state.revfx.index;
  preset_data_set_uint16(i, preset_state.revfx.time); i+=2;
  preset_data_set_uint16(i, preset_state.revfx.depth); i+=2;
  preset_data_set_uint16(i, preset_state.revfx._reserved1); i+=2;
  preset_data_set_uint16(i, preset_state.revfx.mix); i+=2;
  preset_data_set_uint16(i, preset_state.revfx._reserved2); i+=2;

  // arp
  preset_data_buf[i++] = preset_state.arp.index;
  preset_data_buf[i++] = preset_state.arp.intervals;
  preset_data_buf[i++] = preset_state.arp.length;
  preset_data_buf[i++] = preset_state.arp.state;
  preset_data_buf[i++] = preset_state.arp.tempo;

  // lfo
  preset_data_buf[i++] = preset_state.lfo.index;
  preset_data_buf[i++] = preset_state.lfo.rate;
  preset_data_buf[i++] = preset_state.lfo.depth;
  preset_data_buf[i++] = preset_state.lfo.bpm_sync;
  preset_data_buf[i++] = preset_state.lfo._reserved1;
  preset_data_buf[i++] = preset_state.lfo._reserved2;

  // scale
  preset_data_buf[i++] = preset_state.scale.index;
  preset_data_buf[i++] = preset_state.scale._reserved;

  // transpose
  preset_data_buf[i++] = preset_state.transpose.offset;
  preset_data_buf[i++] = preset_state.transpose._reserved;

  // stutter
  preset_data_buf[i++] = preset_state.stutter.index;
  preset_data_buf[i++] = preset_state.stutter._reserved;

  // slide
  preset_data_buf[i++] = preset_state.slide.value;
  preset_data_buf[i++] = preset_state.slide.type;

  // rand
  preset_data_buf[i++] = preset_state.rand.pitch;
  preset_data_buf[i++] = preset_state.rand._reserved;
}

//static inline void preset_ram_gpio_init() {
//  auto ram_pin = GpioPin::newPin(GpioPinType::pb2);
//  ram_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
//}

void preset_setup() {
  state_reset_preset(&preset_state);
  state_reset_global(&global_state);
  state_reset_seq(&seq_state);

  //preset_ram_gpio_init();

  preset_event_create(PST_EVT_PRESET_TMP_LOAD, 0, 0);
}

void preset_partial_save_complete() {
  _preset_is_processing = 0;
}

void preset_tmp_load_complate() {
  preset_load_from_buf();
  _preset_is_processing = 0;
  if (preset_state.version != PANEL_VERSION) {
    state_reset_preset(&preset_state);
    preset_event_create(PST_EVT_PRESET_TMP_SAVE, 0, 0);
  }
  app_input.refresh();
}

void preset_tmp_save_complate() {
  _preset_is_processing = 0;
}

static inline void preset_realtime_tmpsave_proc_uint8(uint32_t addr, uint16_t target_value) {
  preset_data_buf[0] = target_value;
  ram_write_request(preset_data_buf, 1, TEMP_PRESET_RAM_ADDRESS + addr, preset_partial_save_complete);
  _preset_is_processing = 1;
}

static inline void preset_realtime_tmpsave_proc_uint16(uint32_t addr, uint16_t target_value) {
  preset_data_set_uint16(0, (uint16_t)target_value);
  ram_write_request(preset_data_buf, 2, TEMP_PRESET_RAM_ADDRESS + addr, preset_partial_save_complete);
  _preset_is_processing = 1;
}

static inline void preset_realtime_tmp_save_process(PresetEventTargetId target_id, uint16_t value) {
  switch (target_id) {
    case PST_EVT_TARGET_OSC_INDEX:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_OSC_INDEX_ADDR, preset_state.osc.index);
      break;
    case PST_EVT_TARGET_OSC_SHAPE:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_OSC_SHAPE_ADDR, preset_state.osc.shape);
      break;
    case PST_EVT_TARGET_OSC_SHIFT_SHAPE:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_OSC_SHIFT_SHAPE_ADDR, preset_state.osc.shift_shape);
      break;
    case PST_EVT_TARGET_OSC_LFO_RATE:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_OSC_LFO_RATE_ADDR, preset_state.osc.lfo_rate);
      break;
    case PST_EVT_TARGET_OSC_LFO_DEPTH:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_OSC_LFO_DEPTH_ADDR, preset_state.osc.lfo_depth);
      break;
    case PST_EVT_TARGET_OSC_CUSTOM_VALUES:
      if (value < OSC_CUSTOM_VALUES_SIZE) {
        preset_realtime_tmpsave_proc_uint8(PRESET_STATE_OSC_CUSTOM_VALUES_ADDR + value, preset_state.osc.custom_values[value]);
      }
      break;
    case PST_EVT_TARGET_FILTER_INDEX:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_FILTER_INDEX_ADDR, preset_state.filter.index);
      break;
    case PST_EVT_TARGET_FILTER_CUTOFF:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_FILTER_CUTOFF_ADDR, preset_state.filter.cutoff);
      break;
    case PST_EVT_TARGET_FILTER_PEAK:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_FILTER_PEAK_ADDR, preset_state.filter.peak);
      break;
    case PST_EVT_TARGET_FILTER_LFO_RATE:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_FILTER_LFO_RATE_ADDR, preset_state.filter.lfo_rate);
      break;
    case PST_EVT_TARGET_FILTER_LFO_DEPTH:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_FILTER_LFO_DEPTH_ADDR, preset_state.filter.lfo_depth);
      break;
    case PST_EVT_TARGET_AMPEG_INDEX:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_AMPEG_INDEX_ADDR, preset_state.ampeg.index);
      break;
    case PST_EVT_TARGET_AMPEG_ATTACK:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_AMPEG_ATTACK_ADDR, preset_state.ampeg.attack);
      break;
    case PST_EVT_TARGET_AMPEG_RELEASE:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_AMPEG_RELEASE_ADDR, preset_state.ampeg.release);
      break;
    case PST_EVT_TARGET_AMPEG_LFO_RATE:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_AMPEG_LFO_RATE_ADDR, preset_state.ampeg.lfo_rate);
      break;
    case PST_EVT_TARGET_AMPEG_LFO_DEPTH:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_AMPEG_LFO_DEPTH_ADDR, preset_state.ampeg.lfo_depth);
      break;
    case PST_EVT_TARGET_MODFX_INDEX:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_MODFX_INDEX_ADDR, preset_state.modfx.index);
      break;
    case PST_EVT_TARGET_MODFX_TIME:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_MODFX_TIME_ADDR, preset_state.modfx.time);
      break;
    case PST_EVT_TARGET_MODFX_DEPTH:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_MODFX_DEPTH_ADDR, preset_state.modfx.depth);
      break;
    case PST_EVT_TARGET_DELFX_INDEX:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_DELFX_INDEX_ADDR, preset_state.delfx.index);
      break;
    case PST_EVT_TARGET_DELFX_TIME:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_DELFX_TIME_ADDR, preset_state.delfx.time);
      break;
    case PST_EVT_TARGET_DELFX_DEPTH:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_DELFX_DEPTH_ADDR, preset_state.delfx.depth);
      break;
    case PST_EVT_TARGET_DELFX_MIX:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_DELFX_MIX_ADDR, preset_state.delfx.mix);
      break;
    case PST_EVT_TARGET_REVFX_INDEX:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_REVFX_INDEX_ADDR, preset_state.revfx.index);
      break;
    case PST_EVT_TARGET_REVFX_TIME:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_REVFX_TIME_ADDR, preset_state.revfx.time);
      break;
    case PST_EVT_TARGET_REVFX_DEPTH:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_REVFX_DEPTH_ADDR, preset_state.revfx.depth);
      break;
    case PST_EVT_TARGET_REVFX_MIX:
      preset_realtime_tmpsave_proc_uint16(PRESET_STATE_REVFX_MIX_ADDR, preset_state.revfx.mix);
      break;
    case PST_EVT_TARGET_ARP_INDEX:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_ARP_INDEX_ADDR, preset_state.arp.index);
      break;
    case PST_EVT_TARGET_ARP_INTERVALS:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_ARP_INTERVALS_ADDR, preset_state.arp.intervals);
      break;
    case PST_EVT_TARGET_ARP_LENGTH:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_ARP_LENGTH_ADDR, preset_state.arp.length);
      break;
    case PST_EVT_TARGET_ARP_STATE:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_ARP_STATE_ADDR, preset_state.arp.state);
      break;
    case PST_EVT_TARGET_ARP_TEMPO:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_ARP_TEMPO_ADDR, preset_state.arp.tempo);
      break;
    case PST_EVT_TARGET_LFO_INDEX:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_LFO_INDEX_ADDR, preset_state.lfo.index);
      break;
    case PST_EVT_TARGET_LFO_RATE:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_LFO_RATE_ADDR, preset_state.lfo.rate);
      break;
    case PST_EVT_TARGET_LFO_DEPTH:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_LFO_DEPTH_ADDR, preset_state.lfo.depth);
      break;
    case PST_EVT_TARGET_LFO_BPM_SYNC:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_LFO_BPM_SYNC_ADDR, preset_state.lfo.bpm_sync);
      break;
    case PST_EVT_TARGET_SCALE_INDEX:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_SCALE_INDEX_ADDR, preset_state.scale.index);
      break;
    case PST_EVT_TARGET_TRANSPOSE_OFFSET:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_TRANSPOSE_OFFSET_ADDR, preset_state.transpose.offset);
      break;
    case PST_EVT_TARGET_STUTTER_INDEX:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_STUTTER_INDEX_ADDR, preset_state.stutter.index);
      break;
    case PST_EVT_TARGET_SLIDE_VALUE:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_SLIDE_VALUE_ADDR, preset_state.slide.value);
      break;
    case PST_EVT_TARGET_SLIDE_TYPE:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_SLIDE_TYPE_ADDR, preset_state.slide.type);
      break;
    case PST_EVT_TARGET_RAND_PITCH:
      preset_realtime_tmpsave_proc_uint8(PRESET_STATE_RAND_PITCH_ADDR, preset_state.rand.pitch);
      break;
    case PST_EVT_TARGET_NONE:
      break;
  }
}

void preset_process() {
  if (preset_is_processing()) { return; }
  PresetEvent event = preset_event_get();
  switch (event.command_id) {
    case PST_EVT_PRESET_SAVE:
      break;
    case PST_EVT_PRESET_LOAD:
      break;
    case PST_EVT_PRESET_TMP_SAVE:
      preset_save_to_buf();
      ram_write_request(preset_data_buf, PRESET_STATE_SIZE, TEMP_PRESET_RAM_ADDRESS, preset_tmp_save_complate);
      _preset_is_processing = 1;
      break;
    case PST_EVT_PRESET_TMP_LOAD:
      ram_read_request(preset_data_buf, PRESET_STATE_SIZE, TEMP_PRESET_RAM_ADDRESS, preset_tmp_load_complate);
      _preset_is_processing = 1;
      break;
    case PST_EVT_REALTIME_TMP_SAVE:
      preset_realtime_tmp_save_process(event.target_id, event.value);
      break;
    default:
      break;
  }
}

void preset_temporary_save() {
}

void preset_save(uint8_t idx) {
  PresetEvent event = {PST_EVT_PRESET_SAVE, 0, 0};
  preset_event_add(event);
}

void preset_seq_save(uint8_t idx) {
}

void preset_global_save() {
}

void preset_load(uint8_t idx) {
  PresetEvent event = {PST_EVT_PRESET_LOAD, 0, 0};
  preset_event_add(event);
}

void preset_seq_load(uint8_t idx) {
}

void preset_global_load() {
}

uint8_t preset_is_processing() {
  return _preset_is_processing || ram_is_processing();
}

