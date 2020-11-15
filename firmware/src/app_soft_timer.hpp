#ifndef N1GP_APP_SOFT_TIMER_H
#define N1GP_APP_SOFT_TIMER_H

#include <igb_sdk/util/soft_timer.hpp>

constexpr size_t APP_SOFT_TIMER_MAX = 10;

using AppSoftTimer = igb::sdk::SoftTimer<APP_SOFT_TIMER_MAX>;

extern AppSoftTimer app_soft_timer;

#endif /* N1GP_APP_SOFT_TIMER_H */
