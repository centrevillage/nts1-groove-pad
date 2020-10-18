#include "state.h"

void state_reset_preset(PresetState* preset) {
  preset->version = PANEL_VERSION;

  preset->osc.index = 0;
  preset->osc.shape = 0;
  preset->osc.shift_shape = 0;
  preset->osc.lfo_rate = 0;
  preset->osc.lfo_depth = 0;
  preset->osc.custom_index = 0;
  for (uint8_t i=0;i<OSC_CUSTOM_VALUES_SIZE;++i) {
    preset->osc.custom_values[i] = 0;
    preset->osc.custom_value_types[i] = 0;
  }

  preset->filter.index = 0;
  preset->filter.cutoff = 0;
  preset->filter.peak = 0;
  preset->filter.lfo_rate = 0;
  preset->filter.lfo_depth = 0;

  preset->ampeg.index = 0;
  preset->ampeg.attack = 0;
  preset->ampeg.release = 0;
  preset->ampeg.lfo_rate = 0;
  preset->ampeg.lfo_depth = 0;

  preset->modfx.index = 0;
  preset->modfx.time = 0;
  preset->modfx.depth = 0;

  preset->delfx.index = 0;
  preset->delfx.time = 0;
  preset->delfx.depth = 0;
  preset->delfx.mix = 0;

  preset->revfx.index = 0;
  preset->revfx.time = 0;
  preset->revfx.depth = 0;
  preset->revfx.mix = 0;

  preset->arp.index = 0;
  preset->arp.intervals = 0;
  preset->arp.length = 0;
  preset->arp.state = 0;
  preset->arp.tempo = 0;

  preset->lfo.index = 0;
  preset->lfo.rate  = 0;
  preset->lfo.depth = 0;
  preset->lfo.bpm_sync = 0;

  preset->scale.index = 0;
  
  preset->transpose.offset = 0;

  preset->stutter.index = 0;

  preset->stutter.index = 0;

  preset->slide.value = 0;
  preset->slide.type = 0;

  preset->rand.pitch = 0;
}

void state_reset_global(GlobalState* global) {
  global->panel_version = PANEL_VERSION;
  global->nts1_version = 0;
  global->input_route = 0;
  global->input_trim = 0;
  global->syncout_polarity = 0;
  global->syncin_polarity = 0;
  global->tempo_range = 0;
  global->clock_source = 0;
  global->short_message = 0;
  global->midi_route = 0;
  global->midi_channel = 0;
  global->sync_step = 0;

  for (uint8_t i=0;i<SCALE_PRESET_SIZE;++i) {
    for (uint8_t j=0;j<SCALE_OFFSETS_SIZE;++j) {
      global->scale_preset[i].offsets[j] = 0;
    }
  }
}

void state_reset_seq(SeqState* seq) {
  seq->active_steps = 0xFFFF;
  seq->length = 16;
  seq->direction = 0;

  for (uint8_t i=0;i<16;++i) {
    seq->steps[i].note = 64;
    seq->steps[i].velocity = 100;
    seq->steps[i].length = 127;
  }
}
