
#include "pico_core1_alarm_pool.h"

#include <hardware/timer.h>

// alarm_pool_create(uint hardware_alarm_num, uint max_timers);
// hardware_alarm_num 3 is occupied by default pool so use 0,1 or 2
alarm_pool_t * core1_alarm_pool = NULL;

alarm_pool_t * get_core1_alarm_pool()
{
    if(!core1_alarm_pool)
        core1_alarm_pool = alarm_pool_create(2, 6);
    return core1_alarm_pool;
}
