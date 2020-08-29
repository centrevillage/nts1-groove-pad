#ifndef USER_CONF_H
#define USER_CONF_H

// 利用するタイマーのID
//#define TIM_COMMON_ID 2
//#define TIM_SPI_ID 4
//#define TIM_SEQ_ID 5

#define TIM_COMMON TIM14
#define TIM_SPI    TIM16
#define TIM_SEQ    TIM17

#define TIM_COMMON_TYPE TimType::tim14
#define TIM_SPI_TYPE    TimType::tim16
#define TIM_SEQ_TYPE    TimType::tim17

#define TIM_COMMON_HANDLER TIM14_IRQHandler
#define TIM_SPI_HANDLER    TIM16_IRQHandler
#define TIM_SEQ_HANDLER    TIM17_IRQHandler

// クロック/シーケンサーの設定
#define SEQ_TRACK_SIZE 1
#define SEQ_STEP_SIZE 16
#define MICRO_COUNTS_PER_STEP 12
#define MIDI_CLOCK_PER_STEP 6


#endif /* USER_CONF_H */
