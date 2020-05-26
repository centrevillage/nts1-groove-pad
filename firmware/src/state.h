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
  uint8_t shape;
  uint8_t shift_shape;
  uint8_t lfo_rate;
  uint8_t lfo_depth;
  uint8_t custom_index;
  uint8_t custom_values[OSC_CUSTOM_VALUES_SIZE];
  uint8_t custom_value_types[OSC_CUSTOM_VALUES_SIZE];
  uint8_t custom_value_selected_page; // 選択中のページIDX
} OscState;

typedef struct {
  uint8_t index; 
  uint8_t cutoff;
  uint8_t peak;
  uint8_t lfo_rate;
  uint8_t lfo_depth;
  uint8_t _reserved1;
} FilterState;

typedef struct {
  uint8_t index;
  uint8_t attack;
  uint8_t release;
  uint8_t lfo_rate;
  uint8_t lfo_depth;
  uint8_t _reserved1;
} AmpEgState;

typedef struct {
  uint8_t index;
  uint8_t time;
  uint8_t depth;
  uint8_t _reserved1;
  uint8_t _reserved2;
  uint8_t _reserved3;
} ModFxState;

typedef struct {
  uint8_t index;
  uint8_t time;
  uint8_t depth;
  uint8_t _reserved1;
  uint8_t mix;
  uint8_t _reserved2;
} DelFxState;

typedef struct {
  uint8_t index;
  uint8_t time;
  uint8_t depth;
  uint8_t _reserved1;
  uint8_t mix;
  uint8_t _reserved2;
} RevFxState;

typedef struct {
  uint8_t index;
  uint8_t intervals;
  uint8_t length;
  uint8_t state;
  uint8_t tempo;
} ArpState;
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

typedef struct {
  uint8_t index;
  uint8_t _reserved;
} ScaleState;

typedef struct {
  uint8_t offset;
  uint8_t _reserved;
} TransposeState;

typedef struct {
  uint8_t index;
  uint8_t _reserved;
} StutterState;

typedef struct {
  uint8_t value;
  uint8_t type;
} SlideState;

typedef struct {
  uint8_t pitch;
  uint8_t _reserved;
} RandState;

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

typedef struct {
  OscState osc;  
  FilterState filter;
  AmpEgState ampeg;
  ModFxState modfx;
  DelFxState delfx;
  RevFxState revfx;
  ArpState arp;

  LfoState lfo;
  ScaleState scale;
  TransposeState transpose;
  StutterState stutter;
  SlideState slide;
  RandState rand;
} PresetState;

#define MOTION_VALUES_SIZE 5
typedef struct {
  uint8_t note;
  uint8_t velocity;
  uint8_t length;
  uint8_t motion_values[MOTION_VALUES_SIZE];
} SeqStepState;

typedef struct {
  uint16_t active_steps;
  uint16_t active_slides;
  uint8_t start;
  uint8_t length;
  uint8_t direction;
  uint8_t clock_div;
  
  SeqStepState steps[16];
} SeqState;

void state_reset_preset(PresetState* preset);
void state_reset_global(GlobalState* global);
void state_reset_seq(SeqState* seq);

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_STATE_H__ */
