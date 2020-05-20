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
} ModFxDef;

typedef struct {
  char name[PARAM_NAME_LEN];
} DelFxDef;

typedef struct {
  char name[PARAM_NAME_LEN];
} RevFxDef;

#define OSC_DEFS_SIZE 16
extern volatile OscDef osc_defs[OSC_DEFS_SIZE];
#define MODFX_DEFS_SIZE 16
extern volatile ModFxDef modfx_defs[MODFX_DEFS_SIZE];
#define DELFX_DEFS_SIZE 16
extern volatile DelFxDef delfx_defs[DELFX_DEFS_SIZE];
#define REVFX_DEFS_SIZE 16
extern volatile RevFxDef revfx_defs[REVFX_DEFS_SIZE];

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
void nts1_defs_unit_desc_handler(const nts1_rx_unit_desc_t* unit_desc);
void nts1_defs_param_desc_handler(const nts1_rx_edit_param_desc_t* param_desc);

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_NTS1_DEFS_H__ */
