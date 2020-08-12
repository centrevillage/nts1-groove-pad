#ifndef APP_SEQ_H
#define APP_SEQ_H

#include "seq.h"
#include "app_seq_clock.h"
#include "state.h"

struct AppSequencer;
extern AppSequencer seq;

// アプリケーション依存のシーケンサー
// アプリケーション固有の挙動を実現する
struct AppSequencer {
  // 1 トラックのみのシンプルシーケンサー
  Sequencer<SimpleTrack<SimpleSteps>, 1, AppSeqClock> base_seq;

  void init();

  void receiveClock();
  void start();
  void stop();

  void setState(const SeqState& state);
  void getState(SeqState& state);
};


#endif /* APP_SEQ_H */
