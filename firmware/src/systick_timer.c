#include "systick_timer.h"

void systick_timer_setup() {
#ifndef USE_ARDUINO
  /* Setup SysTick Timer for 1 msec interrupts  */
  if (SysTick_Config((SystemCoreClock) / 1000)) { 
    /* Capture error */ 
    while (1);
  }
  NVIC_SetPriority(SysTick_IRQn, 0x0);
#endif
}

#ifndef USE_ARDUINO
volatile uint32_t _current_msec = 0;
void SysTick_Handler(void) {
  _current_msec++;
}
#endif
