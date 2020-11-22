#ifndef IGB_SDK_DEVICE_FRAM_MB85R_SPI_H
#define IGB_SDK_DEVICE_FRAM_MB85R_SPI_H

#include <igb_sdk/base.hpp>
#include <functional>

namespace igb {
namespace sdk {

template<typename GPIO_PIN_TYPE, typename SPI_TYPE>
struct FramMb85rSPI {
  GPIO_PIN_TYPE cs_pin;
  SPI_TYPE spi;

  const size_t block_size = 32;

  enum class AccessState : uint8_t {
    none = 0,
    write,
    read
  };

  AccessState _ram_access_state = AccessState::none;
  uint8_t* _ram_target_buf = nullptr;
  uint32_t _ram_buf_index = 0;
  uint32_t _ram_buf_process_index = 0;
  uint32_t _ram_buf_size = 0;
  uint32_t _ram_address = 0;
  // 関数ポインタでなくstd::functionの方が扱いやすいが、パフォーマンス低下が気になるので・・・
  // 将来的にはfunction_refとかに置き換えたい
  void (*_ram_callback)(void) = nullptr;
  //std::function<void(void)> _ram_callback = nullptr;

  //0000 0110 Set Write Enable Latch
  constexpr static uint8_t FRAM_CMD_WREN = 0x06;
  //0000 0100 Write Disable
  constexpr static uint8_t FRAM_CMD_WRDI = 0x04;
  //0000 0101 Read Status Register
  constexpr static uint8_t FRAM_CMD_RDSR = 0x05;
  //0000 0001 Write Status Register
  constexpr static uint8_t FRAM_CMD_WRSR = 0x01;
  //0000 0011 Read Memory Data
  constexpr static uint8_t FRAM_CMD_READ = 0x03;
  //0000 0010 Write Memory Data
  constexpr static uint8_t FRAM_CMD_WRITE = 0x02;

  inline void requestRead(uint8_t* buf, uint32_t buf_size, uint32_t read_address, void (*callback)(void)) {
  //void requestRead(uint8_t* buf, uint32_t buf_size, uint32_t read_address, std::function<void(void)> callback) {
    if (_ram_access_state == AccessState::none) {
      _ram_target_buf = buf;
      _ram_address = read_address;
      _ram_callback = callback;
      _ram_buf_size = buf_size;
      _ram_buf_index = 0;
      _ram_buf_process_index = 0;
      _ram_access_state = AccessState::read;
    }
  }

  inline void requestWrite(uint8_t* buf, uint32_t buf_size, uint32_t write_address, void (*callback)(void)) {
  //void requestWrite(uint8_t* buf, uint32_t buf_size, uint32_t write_address, std::function<void(void)> callback) {
    if (_ram_access_state == AccessState::none) {
      _ram_target_buf = buf;
      _ram_address = write_address;
      _ram_callback = callback;
      _ram_buf_size = buf_size;
      _ram_buf_index = 0;
      _ram_buf_process_index = 0;
      _ram_access_state = AccessState::write;
    }
  }

  inline void process() {
    switch(_ram_access_state) {
      case AccessState::none:
        break;
      case AccessState::read:
        _processRead();
        break;
      case AccessState::write:
        _processWrite();
        break;
      default:
        break;
    }
  }

  inline bool isProcessing() {
    return _ram_access_state != AccessState::none;
  }

  inline void _writeByte(uint8_t byte) {
    volatile uint8_t tmp = spi.transferU8sync(byte);
  }

  inline uint8_t _readByte() {
    return spi.transferU8sync(0);
  }

  inline void _processRead() {
    cs_pin.low();
    _writeByte(FRAM_CMD_READ);
    _writeByte((_ram_address >> 16) & 0xFF);
    _writeByte((_ram_address >> 8) & 0xFF);
    _writeByte(_ram_address & 0xFF);
    for (size_t i=0; i<block_size && _ram_buf_index < _ram_buf_size; ++i) {
      _ram_target_buf[_ram_buf_index++] = _readByte();
      _ram_address++;
    }
    cs_pin.high();
    if (_ram_buf_index >= _ram_buf_size) {
      _ram_access_state = AccessState::none;
      if (_ram_callback) {
        _ram_callback();
      }
    }
  }

  inline void _processWrite() {
    cs_pin.low();
    _writeByte(FRAM_CMD_WREN); // FRAMの書き込みを有効化
    cs_pin.high();

    cs_pin.low();
    _writeByte(FRAM_CMD_WRITE);
    _writeByte((_ram_address >> 16) & 0xFF);
    _writeByte((_ram_address >> 8) & 0xFF);
    _writeByte(_ram_address & 0xFF);

    for (size_t i=0; i<block_size && _ram_buf_index < _ram_buf_size; ++i) {
      _writeByte(_ram_target_buf[_ram_buf_index++]);
      _ram_address++;
    }
    cs_pin.high();
    if (_ram_buf_index >= _ram_buf_size) {
      _ram_access_state = AccessState::none;
      if (_ram_callback) {
        _ram_callback();
      }
    }
  }
};

}
}

#endif /* IGB_SDK_DEVICE_FRAM_MB85R_SPI_H */
