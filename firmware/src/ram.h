#ifndef __STM_RAM_H
#define __STM_RAM_H

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * MEMO:
 * RAMアクセスは処理中断に対応できなくてはならないため、下記の状態を保持する。
 * ・NONE -> 何も処理が行われていない 
 * ・WRITING -> 書き込み途中の状態。次の書き込み先アドレスと読み込み元アドレス及び残りバイト数を保持
 *      -> プリセット構造体のアドレスは書き込み処理をグループ化した関数ポインタの集合になる
 * ・READING -> 読み込み途中の状態。次の読み込み先アドレスと及び残りバイト数と書き込み先アドレスを保持。
 * ・WRITE_REQUESTED -> 書き込み処理要求状態。書き込み対象プリセットを保持
 * ・READ_REQUESTED -> 読み込み処理要求状態。読み込み対象プリセットを保持
 *
 */

#define RAM_PROCESS_BLOCK 32
#define SPI_RAM_CS_PIN PIN_B2 

typedef enum { 
  RAM_ACCESS_STATE_NONE=0,
  RAM_ACCESS_STATE_WRITE,
  RAM_ACCESS_STATE_READ,
} RamAccessState;

extern volatile RamAccessState ram_access_state;

void ram_read_request(uint8_t* buf, uint32_t buf_size, uint32_t read_address, void (*callback)(void));
void ram_write_request(uint8_t* buf, uint32_t buf_size, uint32_t write_address, void (*callback)(void));

void ram_process();

#ifdef __cplusplus
}
#endif

#endif /* __STM_RAM_H */
