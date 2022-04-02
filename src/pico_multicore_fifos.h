#ifndef pico_multicore_fifos_h
#define pico_multicore_fifos_h

/**
 * @brief Pico SDK multicore fifo helpers
 * 
 */

#include <pico/stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

void send_float(float value);

float receive_float();
bool receive_float_timeout_us(uint64_t timeout_us, float *out);

#ifdef __cplusplus
}
#endif

#endif
