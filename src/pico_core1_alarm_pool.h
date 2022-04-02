#ifndef pico_core1_alarm_pool_h
#define pico_core1_alarm_pool_h

#include <pico/stdlib.h>
#include "hardware/timer.h"

/**
 * @brief Pico SDK core1 alarm pool
 * 
 */

#ifdef __cplusplus
extern "C" {
#endif

alarm_pool_t * get_core1_alarm_pool();

#ifdef __cplusplus
}
#endif

#endif
