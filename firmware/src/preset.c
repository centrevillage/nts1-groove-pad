#include "preset.h"
#include "preset_event.h"
#include "ram.h"
#include "stm32f0xx_ll_gpio.h"
#include "input.h"

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

static inline void preset_ram_gpio_init() {
  LL_GPIO_InitTypeDef gpio;
  gpio.Mode = LL_GPIO_MODE_OUTPUT;
  gpio.Pull = LL_GPIO_PULL_NO;
  gpio.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  gpio.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  gpio.Pin = get_gpio_pin_bits(SPI_RAM_CS_PIN);
  LL_GPIO_Init(get_gpio_typedef(SPI_RAM_CS_PIN), &gpio);
}

void preset_setup() {
  state_reset_preset(&preset_state);
  state_reset_global(&global_state);
  state_reset_seq(&seq_state);

  preset_ram_gpio_init();

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
  input_refresh();
}

void preset_tmp_save_complate() {
  _preset_is_processing = 0;
}

void preset_process() {
  if (preset_is_processing()) { return; }
  PresetEvent event = preset_event_get();
  switch (event.command_id) {
    case PST_EVT_PRESET_SAVE:
      break;
    case PST_EVT_PRESET_LOAD:
      break;
    case PST_EVT_OSC_SHAPE_TMP_SAVE:
      preset_data_set_uint16(0, (uint16_t)preset_state.osc.shape);
      ram_write_request(preset_data_buf, 2,
          TEMP_PRESET_RAM_ADDRESS + PRESET_STATE_OSC_SHAPE_ADDR,
          preset_partial_save_complete);
      _preset_is_processing = 1;
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
  return _preset_is_processing || ram_access_state != RAM_ACCESS_STATE_NONE;
}

