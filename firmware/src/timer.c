#include "timer.h"

void systick_timer_setup() {
  /* Setup SysTick Timer for 1 msec interrupts  */
  if (SysTick_Config((SystemCoreClock) / 1000)) { 
    /* Capture error */ 
    while (1);
  }
  NVIC_SetPriority(SysTick_IRQn, 0x0);
}

void timer_setup() {
  //systick_timer_setup();
}

//volatile uint32_t _current_msec;
//void SysTick_Handler() {
//  ++_current_msec;
//}
