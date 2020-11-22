#ifndef IGB_SDK_SEQ_ALGORITHM_H
#define IGB_SDK_SEQ_ALGORITHM_H

namespace igb {
namespace sdk {

// NOTE: 
// 将来的に動的リンクを行うことを想定してenum classをあえて利用していない。

// 0-127 is user defined event
typedef enum {
  SEQ_EVT_CLOCK = 128,
  SEQ_EVT_START,
  SEQ_EVT_STOP,
  SEQ_EVT_RESET,
  SEQ_EVT_JUMP,
} SeqEventID;

// 0-127 is user defined parameter
typedef enum {
  SEQ_PARAM_STEP = 128,
} SeqParamID;

typedef enum {
  SEQ_PRAM_TYPE_NUMBER = 0,
} SeqParamType;

struct SeqNullAlgorithm {
  void process(uint8_t id, uint8_t sub_id, int16_t value) {
  }
  void setParamIn(uint8_t param_id, int16_t value) {
    setParamIn(param_id, 0, value);
  }
  // for array parameter
  void setParamIn(uint8_t param_id, uint8_t idx, int16_t value) {
  }
  int16_t getParamIn(uint8_t param_id) {
    return 0;
  }
  uint8_t getParamInType(uint8_t param_id) {
    return 0;
  }
  // number of the input parameters
  uint8_t paramInSize() {
    return 0;
  }
  // number of the output parameters
  uint8_t paramOutSize() {
    return 0;
  }
  // array size of the array parameter
  uint8_t arraySize(uint8_t param_id) {
    return 0;
  }
  // serialize api
  uint32_t serializedBufferSize() {
    return 0;
  }
  void serialize(uint8_t* out_buffer, size_t size /* must be equal to serializedBufferSize */ ) {
  }
  void deserialize(uint8_t* in_buffer, size_t size /* must be equal to serializedBufferSize */ ) {
  }
};

struct SeqForwardAlgorithm {
};

}
}

#endif /* IGB_SDK_SEQ_ALGORITHM_H */
