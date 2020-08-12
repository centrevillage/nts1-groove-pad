#ifndef __N1GP_STATE_H__
#define __N1GP_STATE_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PARAM_UNDEFINED 255
#define PARAM_NAME_LEN 13

// NTS1 Parameters {{{
#define OSC_CUSTOM_VALUES_SIZE 6
typedef struct {
  uint8_t index; 
  uint16_t shape;
  uint16_t shift_shape;
  uint16_t lfo_rate;
  uint16_t lfo_depth;
  uint8_t custom_index;
  uint8_t custom_values[OSC_CUSTOM_VALUES_SIZE];
  uint8_t custom_value_types[OSC_CUSTOM_VALUES_SIZE];
  uint8_t custom_value_selected_page; // 選択中のページIDX
} OscState;
// 23 bytes

typedef struct {
  uint8_t index; 
  uint16_t cutoff;
  uint16_t peak;
  uint16_t lfo_rate;
  uint16_t lfo_depth;
  uint16_t _reserved1;
} FilterState;
// 11 bytes

typedef struct {
  uint8_t index;
  uint16_t attack;
  uint16_t release;
  uint16_t lfo_rate;
  uint16_t lfo_depth;
  uint16_t _reserved1;
} AmpEgState;
// 11 bytes

typedef struct {
  uint8_t index;
  uint16_t time;
  uint16_t depth;
  uint16_t _reserved1;
  uint16_t _reserved2;
  uint16_t _reserved3;
} ModFxState;
// 11 bytes

typedef struct {
  uint8_t index;
  uint16_t time;
  uint16_t depth;
  uint16_t _reserved1;
  uint16_t mix;
  uint16_t _reserved2;
} DelFxState;
// 11 bytes

typedef struct {
  uint8_t index;
  uint16_t time;
  uint16_t depth;
  uint16_t _reserved1;
  uint16_t mix;
  uint16_t _reserved2;
} RevFxState;
// 11 bytes

typedef struct {
  uint8_t index;
  uint8_t intervals;
  uint8_t length;
  uint8_t state;
  uint8_t tempo;
} ArpState;
// 5 bytes

// }}} NTS1 Parameters

// Groove Controller Parameters {{{
typedef enum {
  LFO_TYPE_TRI = 0,
  LFO_TYPE_SAW,
  LFO_TYPE_RAMP,
  LFO_TYPE_SQR,
  LFO_TYPE_SIN,
} LfoType;

typedef struct {
  uint8_t index;
  uint8_t rate; 
  uint8_t depth;
  uint8_t bpm_sync;
  uint8_t _reserved1;
  uint8_t _reserved2;
} LfoState;
// 6 bytes

typedef struct {
  uint8_t index;
  uint8_t _reserved;
} ScaleState;
// 2 bytes

typedef struct {
  uint8_t offset;
  uint8_t _reserved;
} TransposeState;
// 2 bytes

typedef struct {
  uint8_t index;
  uint8_t _reserved;
} StutterState;
// 2 bytes

typedef struct {
  uint8_t value;
  uint8_t type;
} SlideState;
// 2 bytes

typedef struct {
  uint8_t pitch;
  uint8_t _reserved;
} RandState;
// 2 bytes

#define SCALE_PRESET_SIZE 16
#define SCALE_OFFSETS_SIZE 12
typedef struct {
  int8_t offsets[SCALE_OFFSETS_SIZE];
} ScalePreset;

// }}} Groove Controller Parameters

typedef struct {
  uint8_t panel_version;
  uint8_t nts1_version;
  uint8_t input_route;
  uint8_t input_trim;
  uint8_t syncout_polarity;
  uint8_t syncin_polarity;
  uint8_t tempo_range;
  uint8_t clock_source;
  uint8_t short_message;
  uint8_t midi_route;
  uint8_t midi_channel;
  uint8_t sync_step;
  uint8_t _reserved1;
  uint8_t _reserved2;
  uint8_t _reserved3;
  uint8_t _reserved4;

  ScalePreset scale_preset[SCALE_PRESET_SIZE];
} GlobalState;
// 208 bytes

#define GLOBAL_STATE_PANEL_VERSION_ADDR 0
#define GLOBAL_STATE_NTS1_VERSION_ADDR (GLOBAL_STATE_PANEL_VERSION_ADDR + 1)
#define GLOBAL_STATE_INPUT_ROUTE_ADDR (GLOBAL_STATE_NTS1_VERSION_ADDR + 1)
#define GLOBAL_STATE_INPUT_TRIM_ADDR (GLOBAL_STATE_INPUT_ROUTE_ADDR + 1)
#define GLOBAL_STATE_SYNCOUT_POLARITY_ADDR (GLOBAL_STATE_INPUT_TRIM_ADDR + 1)
#define GLOBAL_STATE_SYNCIN_POLARITY_ADDR (GLOBAL_STATE_SYNCOUT_POLARITY_ADDR + 1)
#define GLOBAL_STATE_TEMPO_RANGE_ADDR (GLOBAL_STATE_SYNCIN_POLARITY_ADDR + 1)
#define GLOBAL_STATE_CLOCK_SOURCE_ADDR (GLOBAL_STATE_TEMPO_RANGE_ADDR + 1)
#define GLOBAL_STATE_SHORT_MESSAGE_ADDR (GLOBAL_STATE_CLOCK_SOURCE_ADDR + 1)
#define GLOBAL_STATE_MIDI_ROUTE_ADDR (GLOBAL_STATE_SHORT_MESSAGE_ADDR + 1)
#define GLOBAL_STATE_MIDI_CHANNEL_ADDR (GLOBAL_STATE_MIDI_ROUTE_ADDR + 1)
#define GLOBAL_STATE_SYNC_STEP_ADDR (GLOBAL_STATE_MIDI_CHANNEL_ADDR + 1)
#define GLOBAL_STATE_RESERVED1_ADDR (GLOBAL_STATE_SYNC_STEP_ADDR + 1)
#define GLOBAL_STATE_RESERVED2_ADDR (GLOBAL_STATE_RESERVED1_ADDR + 1)
#define GLOBAL_STATE_RESERVED3_ADDR (GLOBAL_STATE_RESERVED2_ADDR + 1)
#define GLOBAL_STATE_RESERVED4_ADDR (GLOBAL_STATE_RESERVED3_ADDR + 1)
#define GLOBAL_STATE_SCALE_PRESET_ADDR (GLOBAL_STATE_RESERVED4_ADDR + 1)

#define GLOBAL_STATE_BYTE_SIZE (GLOBAL_STATE_SCALE_PRESET_ADDR + (SCALE_PRESET_SIZE * SCALE_OFFSETS_SIZE))

#define GLOBAL_BLOCK_SIZE 256

typedef struct {
  uint8_t version;          //  1 bytes
  OscState osc;             // 23 bytes
  FilterState filter;       // 11 bytes
  AmpEgState ampeg;         // 11 bytes
  ModFxState modfx;         // 11 bytes
  DelFxState delfx;         // 11 bytes
  RevFxState revfx;         // 11 bytes
  ArpState arp;             //  5 bytes

  LfoState lfo;             //  6 bytes
  ScaleState scale;         //  2 bytes
  TransposeState transpose; //  2 bytes
  StutterState stutter;     //  2 bytes
  SlideState slide;         //  2 bytes
  RandState rand;           //  2 bytes
} PresetState;
// 100 bytes

#define PRESET_STATE_VERSION_ADDR 0
#define PRESET_STATE_OSC_INDEX_ADDR 1
#define PRESET_STATE_OSC_SHAPE_ADDR (PRESET_STATE_OSC_INDEX_ADDR + 1)
#define PRESET_STATE_OSC_SHIFT_SHAPE_ADDR (PRESET_STATE_OSC_SHAPE_ADDR + 2)
#define PRESET_STATE_OSC_LFO_RATE_ADDR (PRESET_STATE_OSC_SHIFT_SHAPE_ADDR + 2)
#define PRESET_STATE_OSC_LFO_DEPTH_ADDR (PRESET_STATE_OSC_LFO_RATE_ADDR + 2)
#define PRESET_STATE_OSC_CUSTOM_INDEX_ADDR (PRESET_STATE_OSC_LFO_DEPTH_ADDR + 2)
#define PRESET_STATE_OSC_CUSTOM_VALUES_ADDR (PRESET_STATE_OSC_CUSTOM_INDEX_ADDR + 1)
#define PRESET_STATE_OSC_CUSTOM_VALUE_TYPES_ADDR (PRESET_STATE_OSC_CUSTOM_VALUES_ADDR + OSC_CUSTOM_VALUES_SIZE)
#define PRESET_STATE_OSC_CUSTOM_VALUE_SELECTED_PAGE (PRESET_STATE_OSC_CUSTOM_VALUE_TYPES_ADDR + OSC_CUSTOM_VALUES_SIZE)

#define PRESET_STATE_FILTER_INDEX_ADDR (PRESET_STATE_OSC_CUSTOM_VALUE_SELECTED_PAGE + 1)
#define PRESET_STATE_FILTER_CUTOFF_ADDR (PRESET_STATE_FILTER_INDEX_ADDR + 1)
#define PRESET_STATE_FILTER_PEAK_ADDR (PRESET_STATE_FILTER_CUTOFF_ADDR + 2)
#define PRESET_STATE_FILTER_LFO_RATE_ADDR (PRESET_STATE_FILTER_PEAK_ADDR + 2)
#define PRESET_STATE_FILTER_LFO_DEPTH_ADDR (PRESET_STATE_FILTER_LFO_RATE_ADDR + 2)
#define PRESET_STATE_FILTER_RESERVED1_ADDR (PRESET_STATE_FILTER_LFO_DEPTH_ADDR + 2)

#define PRESET_STATE_AMPEG_INDEX_ADDR (PRESET_STATE_FILTER_RESERVED1_ADDR + 2)
#define PRESET_STATE_AMPEG_ATTACK_ADDR (PRESET_STATE_AMPEG_INDEX_ADDR + 1)
#define PRESET_STATE_AMPEG_RELEASE_ADDR (PRESET_STATE_AMPEG_ATTACK_ADDR + 2)
#define PRESET_STATE_AMPEG_LFO_RATE_ADDR (PRESET_STATE_AMPEG_RELEASE_ADDR + 2)
#define PRESET_STATE_AMPEG_LFO_DEPTH_ADDR (PRESET_STATE_AMPEG_LFO_RATE_ADDR + 2)
#define PRESET_STATE_AMPEG_RESERVED1_ADDR (PRESET_STATE_AMPEG_LFO_DEPTH_ADDR + 2)

#define PRESET_STATE_MODFX_INDEX_ADDR (PRESET_STATE_AMPEG_RESERVED1_ADDR + 2)
#define PRESET_STATE_MODFX_TIME_ADDR (PRESET_STATE_MODFX_INDEX_ADDR + 1)
#define PRESET_STATE_MODFX_DEPTH_ADDR (PRESET_STATE_MODFX_TIME_ADDR + 2)
#define PRESET_STATE_MODFX_RESERVED1_ADDR (PRESET_STATE_MODFX_DEPTH_ADDR + 2)
#define PRESET_STATE_MODFX_RESERVED2_ADDR (PRESET_STATE_MODFX_RESERVED1_ADDR + 2)
#define PRESET_STATE_MODFX_RESERVED3_ADDR (PRESET_STATE_MODFX_RESERVED2_ADDR + 2)

#define PRESET_STATE_DELFX_INDEX_ADDR (PRESET_STATE_MODFX_RESERVED3_ADDR + 2)
#define PRESET_STATE_DELFX_TIME_ADDR (PRESET_STATE_DELFX_INDEX_ADDR + 1)
#define PRESET_STATE_DELFX_DEPTH_ADDR (PRESET_STATE_DELFX_TIME_ADDR + 2)
#define PRESET_STATE_DELFX_RESERVED1_ADDR (PRESET_STATE_DELFX_DEPTH_ADDR + 2)
#define PRESET_STATE_DELFX_MIX_ADDR (PRESET_STATE_DELFX_RESERVED1_ADDR + 2)
#define PRESET_STATE_DELFX_RESERVED2_ADDR (PRESET_STATE_DELFX_MIX_ADDR + 2)

#define PRESET_STATE_REVFX_INDEX_ADDR (PRESET_STATE_DELFX_RESERVED2_ADDR + 2)
#define PRESET_STATE_REVFX_TIME_ADDR (PRESET_STATE_REVFX_INDEX_ADDR + 1)
#define PRESET_STATE_REVFX_DEPTH_ADDR (PRESET_STATE_REVFX_TIME_ADDR + 2)
#define PRESET_STATE_REVFX_RESERVED1_ADDR (PRESET_STATE_REVFX_DEPTH_ADDR + 2)
#define PRESET_STATE_REVFX_MIX_ADDR (PRESET_STATE_REVFX_RESERVED1_ADDR + 2)
#define PRESET_STATE_REVFX_RESERVED2_ADDR (PRESET_STATE_REVFX_MIX_ADDR + 2)

#define PRESET_STATE_ARP_INDEX_ADDR (PRESET_STATE_REVFX_RESERVED2_ADDR + 2)
#define PRESET_STATE_ARP_INTERVALS_ADDR (PRESET_STATE_ARP_INDEX_ADDR + 1)
#define PRESET_STATE_ARP_LENGTH_ADDR (PRESET_STATE_ARP_INTERVALS_ADDR + 1)
#define PRESET_STATE_ARP_STATE_ADDR (PRESET_STATE_ARP_LENGTH_ADDR + 1)
#define PRESET_STATE_ARP_TEMPO_ADDR (PRESET_STATE_ARP_STATE_ADDR + 1)

#define PRESET_STATE_LFO_INDEX_ADDR (PRESET_STATE_ARP_TEMPO_ADDR + 1)
#define PRESET_STATE_LFO_RATE_ADDR (PRESET_STATE_LFO_INDEX_ADDR + 1)
#define PRESET_STATE_LFO_DEPTH_ADDR (PRESET_STATE_LFO_RATE_ADDR + 1)
#define PRESET_STATE_LFO_BPM_SYNC_ADDR (PRESET_STATE_LFO_DEPTH_ADDR + 1)
#define PRESET_STATE_LFO_RESERVED1_ADDR (PRESET_STATE_LFO_BPM_SYNC_ADDR + 1)
#define PRESET_STATE_LFO_RESERVED2_ADDR (PRESET_STATE_LFO_RESERVED1_ADDR + 1)

#define PRESET_STATE_SCALE_INDEX_ADDR (PRESET_STATE_LFO_RESERVED2_ADDR + 1)
#define PRESET_STATE_SCALE_RESERVED_ADDR (PRESET_STATE_SCALE_INDEX_ADDR + 1)

#define PRESET_STATE_TRANSPOSE_OFFSET_ADDR (PRESET_STATE_SCALE_RESERVED_ADDR + 1)
#define PRESET_STATE_TRANSPOSE_RESERVED_ADDR (PRESET_STATE_TRANSPOSE_OFFSET_ADDR + 1)

#define PRESET_STATE_STUTTER_INDEX_ADDR (PRESET_STATE_TRANSPOSE_RESERVED_ADDR + 1)
#define PRESET_STATE_STUTTER_RESERVED_ADDR (PRESET_STATE_STUTTER_INDEX_ADDR + 1)

#define PRESET_STATE_SLIDE_VALUE_ADDR (PRESET_STATE_STUTTER_RESERVED_ADDR + 1)
#define PRESET_STATE_SLIDE_TYPE_ADDR (PRESET_STATE_SLIDE_VALUE_ADDR + 1)

#define PRESET_STATE_RAND_PITCH_ADDR (PRESET_STATE_SLIDE_TYPE_ADDR + 1)
#define PRESET_STATE_RAND_RESERVED_ADDR (PRESET_STATE_RAND_PITCH_ADDR + 1)

#define PRESET_STATE_SIZE (PRESET_STATE_RAND_RESERVED_ADDR + 1)

#define PRESET_BLOCK_SIZE 128

typedef struct {
  uint8_t active_bits;
  uint8_t index;
  int16_t shape;
  int16_t shift_shape;
  int16_t lfo_rate;
  int16_t lfo_depth;
} OscMotion;
// 10 bytes
#define OSC_MOTION_INDEX_ACTIVE_BIT (1)
#define OSC_MOTION_SHAPE_ACTIVE_BIT (1<<1)
#define OSC_MOTION_SHIFT_SHAPE_ACTIVE_BIT (1<<2)
#define OSC_MOTION_LFO_RATE_ACTIVE_BIT (1<<3)
#define OSC_MOTION_LFO_DEPTH_ACTIVE_BIT (1<<4)

typedef struct {
  uint8_t active_bits; // param index
  int16_t values[6];
} ParamMotion;
// 13 bytes

typedef struct {
  uint8_t active_bits;
  uint8_t index;
  uint16_t cutoff;
  uint16_t peak;
  uint16_t lfo_rate;
  uint16_t lfo_depth;
} FilterMotion;
// 10 bytes
#define FILTER_MOTION_INDEX_ACTIVE_BIT (1)
#define FILTER_MOTION_CUTOFF_ACTIVE_BIT (1<<1)
#define FILTER_MOTION_PEAK_ACTIVE_BIT (1<<2)
#define FILTER_MOTION_LFO_RATE_ACTIVE_BIT (1<<3)
#define FILTER_MOTION_LFO_DEPTH_ACTIVE_BIT (1<<4)

typedef struct {
  uint8_t note;             //  1 bytes
  uint8_t velocity;         //  1 bytes
  uint8_t length;           //  1 bytes

  // motion values
  OscMotion osc;
  ParamMotion param;
  FilterMotion filter;

  // TODO:
} SeqStepState;

#define SEQ_STEP_SIZE 16

typedef struct {
  uint16_t active_steps;
  uint8_t length;
  uint8_t direction;
  
  SeqStepState steps[SEQ_STEP_SIZE];
} SeqState;

void state_reset_preset(PresetState* preset);
void state_reset_global(GlobalState* global);
void state_reset_seq(SeqState* seq);

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_STATE_H__ */
