#ifndef __N1GP_NTS1_DEFS_H__
#define __N1GP_NTS1_DEFS_H__

#include "main.h"
#include "state.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  char name[PARAM_NAME_LEN];
  uint8_t value_type;
  int8_t min;
  int8_t max;
} ParamDef;

typedef struct {
  char name[PARAM_NAME_LEN];
  uint8_t param_count;
  ParamDef params[OSC_CUSTOM_VALUES_SIZE];
} OscDef;

typedef struct {
  char name[PARAM_NAME_LEN];
} FilterDef;

typedef struct {
  char name[PARAM_NAME_LEN];
} AmpEgDef;

typedef struct {
  char name[PARAM_NAME_LEN];
} ModFxDef;

typedef struct {
  char name[PARAM_NAME_LEN];
} DelFxDef;

typedef struct {
  char name[PARAM_NAME_LEN];
} RevFxDef;

typedef struct {
  char name[PARAM_NAME_LEN];
} ArpPatDef;

typedef struct {
  char name[PARAM_NAME_LEN];
} ArpIntervalsDef;

#define OSC_DEFS_SIZE 32
extern volatile OscDef osc_defs[OSC_DEFS_SIZE];
extern volatile uint8_t osc_defs_size;
#define FILTER_DEFS_SIZE 12
extern volatile FilterDef filter_defs[FILTER_DEFS_SIZE];
extern volatile uint8_t filter_defs_size;
#define AMPEG_DEFS_SIZE 8
extern volatile AmpEgDef ampeg_defs[AMPEG_DEFS_SIZE];
extern volatile uint8_t ampeg_defs_size;
#define MODFX_DEFS_SIZE 32
extern volatile ModFxDef modfx_defs[MODFX_DEFS_SIZE];
extern volatile uint8_t modfx_defs_size;
#define DELFX_DEFS_SIZE 32
extern volatile DelFxDef delfx_defs[DELFX_DEFS_SIZE];
extern volatile uint8_t delfx_defs_size;
#define REVFX_DEFS_SIZE 32
extern volatile RevFxDef revfx_defs[REVFX_DEFS_SIZE];
extern volatile uint8_t revfx_defs_size;
#define ARPPAT_DEFS_SIZE 16
extern volatile ArpPatDef arppat_defs[ARPPAT_DEFS_SIZE];
extern volatile uint8_t arppat_defs_size;
#define ARPINT_DEFS_SIZE 16
extern volatile ArpIntervalsDef arpint_defs[ARPINT_DEFS_SIZE];
extern volatile uint8_t arpint_defs_size;

#define DEFAULT_OSC_NAMES_SIZE 4
static const char* default_osc_names[DEFAULT_OSC_NAMES_SIZE] = {
  "SAW",
  "TRI",
  "SQR",
  "VPM"
};

#define DEFAULT_FILTER_NAMES_SIZE 7
static const char* default_filter_names[DEFAULT_FILTER_NAMES_SIZE] = {
  "LP2",
  "LP4",
  "BP2",
  "BP4",
  "HP2",
  "HP4",
  "OFF"
};

#define DEFAULT_AMPEG_NAMES_SIZE 5
static const char* default_ampeg_names[DEFAULT_AMPEG_NAMES_SIZE] = {
  "ADSR",
  "AHR",
  "AR",
  "AR LOOP",
  "OPEN"
};

void nts1_defs_req_load();
void nts1_defs_process_loading();
uint8_t nts1_defs_is_complete_loading();
void nts1_defs_unit_desc_handler(const nts1_rx_unit_desc_t* unit_desc);
void nts1_defs_param_desc_handler(const nts1_rx_edit_param_desc_t* param_desc);
void nts1_defs_param_value_handler(const nts1_rx_value_t* value);

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_NTS1_DEFS_H__ */
