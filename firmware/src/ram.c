#include "ram.h"
#include "spi.h"
#include "stm32_pinconfig.h"

// TODO: configuration
#define SPI_RAM_IDX 0

//0000 0110 Set Write Enable Latch
#define FRAM_CMD_WREN 0x06
//0000 0100 Write Disable
#define FRAM_CMD_WRDI 0x04
//0000 0101 Read Status Register
#define FRAM_CMD_RDSR 0x05
//0000 0001 Write Status Register
#define FRAM_CMD_WRSR 0x01
//0000 0011 Read Memory Data
#define FRAM_CMD_READ 0x03
//0000 0010 Write Memory Data
#define FRAM_CMD_WRITE 0x02


volatile RamAccessState ram_access_state = RAM_ACCESS_STATE_NONE;

static volatile uint8_t* ram_target_buf;
static volatile uint32_t ram_buf_index;
static volatile uint32_t ram_buf_process_index;
static volatile uint32_t ram_buf_size;
static volatile uint32_t ram_address;
void (*ram_callback)(void);

void ram_read_request(uint8_t* buf, uint32_t buf_size, uint32_t read_address, void (*callback)(void)) {
  if (ram_access_state == RAM_ACCESS_STATE_NONE) {
    ram_target_buf = buf;
    ram_address = read_address;
    ram_callback = callback;
    ram_buf_size = buf_size;
    ram_buf_index = 0;
    ram_buf_process_index = 0;
    ram_access_state = RAM_ACCESS_STATE_READ;
  }
}

void ram_write_request(uint8_t* buf, uint32_t buf_size, uint32_t write_address, void (*callback)(void)) {
  if (ram_access_state == RAM_ACCESS_STATE_NONE) {
    ram_target_buf = buf;
    ram_address = write_address;
    ram_callback = callback;
    ram_buf_size = buf_size;
    ram_buf_index = 0;
    ram_buf_process_index = 0;
    ram_access_state = RAM_ACCESS_STATE_WRITE;
  }
}

inline void ram_write_byte(uint8_t byte) {
  spi_transmit(SPI_RAM_IDX, byte);
}

inline uint8_t ram_read_byte() {
  return spi_transmit(SPI_RAM_IDX, 0);
}

void ram_process_read() {
  gpio_write(SPI_RAM_CS_PIN, 0);
  ram_write_byte(FRAM_CMD_READ);
  ram_write_byte((ram_address >> 16) & 0xFF);
  ram_write_byte((ram_address >> 8) & 0xFF);
  ram_write_byte(ram_address & 0xFF);
  for (uint8_t i=0; i<RAM_PROCESS_BLOCK && ram_buf_index < ram_buf_size; ++i) {
    ram_target_buf[ram_buf_index++] = ram_read_byte();
    ram_address++;
  }
  gpio_write(SPI_RAM_CS_PIN, 1);
  if (ram_buf_index >= ram_buf_size) {
    ram_access_state = RAM_ACCESS_STATE_NONE;
    if (ram_callback) {
      ram_callback();
    }
  }
}

void ram_process_write() {
  gpio_write(SPI_RAM_CS_PIN, 0);
  ram_write_byte(FRAM_CMD_WREN); // FRAMの書き込みを有効化
  gpio_write(SPI_RAM_CS_PIN, 1);

  gpio_write(SPI_RAM_CS_PIN, 0);
  ram_write_byte(FRAM_CMD_WRITE);
  ram_write_byte((ram_address >> 16) & 0xFF);
  ram_write_byte((ram_address >> 8) & 0xFF);
  ram_write_byte(ram_address & 0xFF);

  for (uint8_t i=0; i<RAM_PROCESS_BLOCK && ram_buf_index < ram_buf_size; ++i) {
    ram_write_byte(ram_target_buf[ram_buf_index++]);
    ram_address++;
  }
  gpio_write(SPI_RAM_CS_PIN, 1);
  if (ram_buf_index >= ram_buf_size) {
    ram_access_state = RAM_ACCESS_STATE_NONE;
    if (ram_callback) {
      ram_callback();
    }
  }
}

void ram_process() {
  switch(ram_access_state) {
    case RAM_ACCESS_STATE_NONE:
      break;
    case RAM_ACCESS_STATE_READ:
      ram_process_read();
      break;
    case RAM_ACCESS_STATE_WRITE:
      ram_process_write();
      break;
  }
}
