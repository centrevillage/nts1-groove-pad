#include "main.h"
#include "button.h"
#include "touch.h"
#include "led.h"
#include "oled.h"
#include "seq.h"

extern "C" {
  void setup();
  void loop();
}

void setup() {
  nts1_init();
  //button_setup();
  //touch_setup();
  led_setup();
  oled_setup();
  //seq_setup();

  //nts1_note_on(100, 100);
}

void loop() {
  nts1_idle();
  led_process();
  oled_process();
}
