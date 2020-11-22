#ifndef N1GP_APP_SCREEN_BASE_H
#define N1GP_APP_SCREEN_BASE_H

#include "main.h"
#include "draw.h"
#include <igb_sdk/util/text.h>
#include "screen_conf.h"
#include "led.h"
#include "app_seq.h"
#include <variant>
#include <functional>
#include <optional>
#include <array>

enum class AppScreenMode {
  edit = 0,
  debug,
  seq
};

#endif /* N1GP_APP_SCREEN_BASE_H */
