#include "ram.h"

#include <igb_stm32/periph/gpio.hpp>
#include <igb_stm32/periph/spi.hpp>
#include <igb_sdk/device/fram_mb85r_spi.hpp>

using namespace igb::stm32;
using namespace igb::sdk;

volatile FramMb85rSPI<GpioPin, Spi> fram = {
  .cs_pin = GpioPin::newPin(GpioPinType::pb2),
  .spi = Spi::newSpi(SpiType::spi1)
};

void ram_setup() {
}

void ram_read_request(uint8_t* buf, uint32_t buf_size, uint32_t read_address, void (*callback)(void)) {
  fram.requestRead(buf, buf_size, read_address, callback);
}

void ram_write_request(uint8_t* buf, uint32_t buf_size, uint32_t write_address, void (*callback)(void)) {
  fram.requestWrite(buf, buf_size, write_address, callback);
}

void ram_process() {
  fram.process();
}

bool ram_is_processing() {
  return fram.isProcessing();
}
