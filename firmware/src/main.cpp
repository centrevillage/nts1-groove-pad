#include "main.h"
#include "button.h"
#include "touch.h"
#include "led.h"
#include "oled.h"
#include "seq.h"
#include "input.h"
#include "timer.h"
#include "debug.h"

extern "C" {
  void setup();
  void loop();
}

void setup() {
  nts1_init();
  //button_setup();
  input_setup();
  led_setup();
  oled_setup();

  //nts1_note_on(100, 100);
  
  debug_text("SETUP", 5); 

  touch_setup();
  timer_event_listen(touch_process);
  timer_setup();
}

void loop() {
  nts1_idle();
  led_process();
  oled_process();
  //touch_process();
}
