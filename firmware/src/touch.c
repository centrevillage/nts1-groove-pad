#include "touch.h"
#include "timer.h"
#include "input.h"
#include <stdlib.h>

#include "stm32f0xx.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_bus.h"

#include "debug.h"

#define THRESHOLD 1000
#define MAX_COUNT 16383

typedef enum {  
  TSC_RELEASE,  
  TSC_PRESSED  
} TSCStatus;  

typedef struct {  
  uint32_t fixed_value;  
  uint32_t current_value;  
  TSCStatus status;  
  uint32_t enable_mask;  
} ChannelStatus;  

ChannelStatus touch_channels[3][3] = {
  { // L
    {2000, 2000, TSC_RELEASE, ((uint32_t)1)<<17},
    {2000, 2000, TSC_RELEASE, ((uint32_t)1)<<18},
    {2000, 2000, TSC_RELEASE, ((uint32_t)1)<<19}
  },
  { // R
    {2000, 2000, TSC_RELEASE, ((uint32_t)1)<<1},
    {2000, 2000, TSC_RELEASE, ((uint32_t)1)<<2},
    {2000, 2000, TSC_RELEASE, ((uint32_t)1)<<3}
  },
  { // center L / R
    {2000, 2000, TSC_RELEASE, ((uint32_t)1)<<9},
    {2000, 2000, TSC_RELEASE, ((uint32_t)1)<<10},
    {2000, 2000, TSC_RELEASE, ((uint32_t)0)<<11}
  }
};

//typedef enum {
//  TPS_READY = 0,
//  TPS_START
//} TouchProcessState;

#define TPS_READY 1
#define TPS_START 0

__IO uint8_t touch_process_state = TPS_READY;
static uint8_t touch_process_index = 0;

//static uint32_t touch_request_msec = 0;

void touch_event_callback_null(uint8_t touch_idx, uint8_t on, uint32_t value) {}

static TouchEventCallback touch_event_callback = touch_event_callback_null;

void touch_event_listen(TouchEventCallback cb) {
  touch_event_callback = cb;
}

void touch_scan_request(uint8_t index) {  
  TSC->IOCCR = touch_channels[0][index].enable_mask | touch_channels[1][index].enable_mask | touch_channels[2][index].enable_mask;
  TSC->ICR |= 0x03; // request clearing MCEF and EOAF flags
  TSC->CR |= 0x02; // start acquisition
  //touch_request_msec = current_msec();
}

uint8_t touch_scan_check_eoc() {  
  //return (TSC->ISR & 0x01) && !(TSC->ISR & 0x02);
  return (TSC->ISR & 0x01);
}

uint8_t touch_scan_check_error() {  
  return TSC->ISR & 0x02;
}

static const uint8_t hard_index_to_touch_idx[3][3] = {
  // L
  {
    2,
    1,
    0
  },
  // R
  {
    5,
    4,
    3
  },
  // center L / R
  {
    6,
    7,
    0
  },
};

void touch_scan_execute() {  
  touch_channels[0][touch_process_index].current_value = TSC->IOGXCR[4];
  touch_channels[1][touch_process_index].current_value = TSC->IOGXCR[0];
  touch_channels[2][touch_process_index].current_value = TSC->IOGXCR[2];

  //if (touch_process_index == 1) {
  //  debug_uint32(touch_channels[1][touch_process_index].current_value);
  //}
 
  for (uint8_t i=0; i<3; ++i) {
    if (touch_channels[i][touch_process_index].current_value == MAX_COUNT) {
      continue;
    }
    int32_t diff = abs(touch_channels[i][touch_process_index].current_value - touch_channels[i][touch_process_index].fixed_value);
    if(diff > THRESHOLD)  {  
      if (touch_channels[i][touch_process_index].status != TSC_PRESSED) {
        touch_channels[i][touch_process_index].status = TSC_PRESSED;  
        touch_event_callback(hard_index_to_touch_idx[i][touch_process_index], 1, touch_channels[i][touch_process_index].current_value);
      }
    }  else  {  
      if (touch_channels[i][touch_process_index].status != TSC_RELEASE) {
        touch_channels[i][touch_process_index].status = TSC_RELEASE;  
        touch_event_callback(hard_index_to_touch_idx[i][touch_process_index], 0, touch_channels[i][touch_process_index].current_value);
      }
    }  
  }
}

void touch_process() {
  //debug_text("T_PROC", 6);
  //debug_uint32((uint32_t)touch_process_state);
 // debug_uint32((uint32_t)TSC->ISR);
  if (touch_process_state == TPS_READY) {
    //debug_text("READY", 5);
    touch_scan_request(touch_process_index);
    touch_process_state = TPS_START;
  } else {
    //debug_text("START", 5);
    if (touch_scan_check_eoc()) {
      //if (!touch_scan_check_error()) {
        touch_scan_execute();
      //}
      touch_process_index = (touch_process_index+1) % 3;
      touch_process_state = TPS_READY;
      //debug_text("*READY", 6);
    }
  }
}

void touch_gpio_setup() {
/*  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);*/
/*  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);*/
/*  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);*/

  LL_GPIO_InitTypeDef GPIO_InitStructure;

  // Alternate function Output Open-Drain for Sampling Capacitor IOs
  //----------------------------------------------------------------
  GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStructure.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStructure.Alternate = LL_GPIO_AF_3;
  // Touch L Cap
  GPIO_InitStructure.Pin = LL_GPIO_PIN_3;
  LL_GPIO_Init(GPIOB, &GPIO_InitStructure);
  // Touch R Cap
  GPIO_InitStructure.Pin = LL_GPIO_PIN_0;
  LL_GPIO_Init(GPIOA, &GPIO_InitStructure);
  // Touch L&R center Cap
  GPIO_InitStructure.Alternate = LL_GPIO_AF_0;
  GPIO_InitStructure.Pin = LL_GPIO_PIN_5;
  LL_GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_InitStructure.Alternate = LL_GPIO_AF_3;

  // Alternate function Output Push-Pull for Channel and Shield IOs
  //---------------------------------------------------------------
  GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  // Touch L
  GPIO_InitStructure.Pin = LL_GPIO_PIN_4 | LL_GPIO_PIN_6 | LL_GPIO_PIN_7;
  LL_GPIO_Init(GPIOB, &GPIO_InitStructure);
  // Touch R
  GPIO_InitStructure.Pin = LL_GPIO_PIN_1 | LL_GPIO_PIN_2 | LL_GPIO_PIN_3;
  LL_GPIO_Init(GPIOA, &GPIO_InitStructure);
  // Touch L&R center
  GPIO_InitStructure.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_1;
  LL_GPIO_Init(GPIOB, &GPIO_InitStructure);

/*  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_3, LL_GPIO_AF_3);*/
/*  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_4, LL_GPIO_AF_3);*/
/*  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_6, LL_GPIO_AF_3);*/
/*  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_7, LL_GPIO_AF_3);*/

/*  LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_0, LL_GPIO_AF_3);*/
/*  LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_1, LL_GPIO_AF_3);*/
/*  LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_2, LL_GPIO_AF_3);*/
/*  LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_3, LL_GPIO_AF_3);*/

/*  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_0, LL_GPIO_AF_3);*/
/*  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_1, LL_GPIO_AF_3);*/
/*  LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_5, LL_GPIO_AF_0);*/

  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_TSC);
}

void touch_tsc_init() {
  //TSC::CR
  //  28-31:CTPH(Change transfer pulse high)
  //  24-27:CCTPL(Change transfer pulse low)
  //  17-23:SSD(Spread spectrum deviation)
  //  16   :SSE(Spread spectrum enable)
  //  15   :SSPSC(Sperad spectrum prescaler)
  //  12-14:PGPSC(pulse generator prescaler)
  //   8-11:Reserved
  //   5- 7:Max count value
  //   4   :IODEF(I/O Default mode)
  //   3   :SYNCPOL(Synchronization pin polarity)
  //   2   :AM(Acquisition mode)
  //   1   :START(Start a new acquisition)
  //   0   :TSCE(Touch sensing controller enable)
  TSC->CR = (1 << 28) | (1 << 24) | (2 << 12) | (6 << 5) | (0 << 2) | (1 << 0);

  //TSC::IOSCR
  // Sampling caps
  //  28-31:G8_IO1-IO4
  //  24-27:G7_IO1-IO4
  //  20-23:G6_IO1-IO4
  //  16-19:G5_IO1-IO4
  //  12-15:G4_IO1-IO4
  //   8-11:G3_IO1-IO4
  //   4- 7:G2_IO1-IO4
  //   0- 3:G1_IO1-IO4
  //----
  // G5_IO1 | G3_IO1 | G1_IO1
  TSC->IOSCR |= (1<<16) | (1<<8) | (1<<0); 

  // disable histeresis control
  TSC->IOHCR = 0;

  //TSC::IOGCSR
  //  15-23:Analog I/O group x status
  //  0 - 7:AAnalog I/O group x enable
  // G5 | G3 | G1
  TSC->IOGCSR |= (1<<4) | (1<<2) | (1<<0) ; 
}

// see stm32f0 reference manulal
void touch_setup() {
  touch_gpio_setup();
  touch_tsc_init();
  touch_process_state = TPS_READY;
  touch_process_index = 0;
}
