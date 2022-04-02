
#include "pico_multicore_fifos.h"

#include <string.h>
#include <pico/multicore.h>

void send_float(float value)
{
    uint32_t float_as_unsigned_words[2];

    memcpy(float_as_unsigned_words, &(value), sizeof(float));
    for(int i = 0; i < 2; i++)
        multicore_fifo_push_blocking(float_as_unsigned_words[i]);
}

float receive_float()
{
    uint32_t float_as_unsigned_words[2];
    float value;

    for(int i = 0; i < 2; i++)
        float_as_unsigned_words[i] = multicore_fifo_pop_blocking();
    memcpy(&value, float_as_unsigned_words, sizeof(float));
    return value;
}

bool receive_float_timeout_us(uint64_t timeout_us, float *out)
{
    uint32_t float_as_unsigned_words[2];
    float value;

    if(multicore_fifo_pop_timeout_us(timeout_us, &float_as_unsigned_words[0]))
    {
        float_as_unsigned_words[1] = multicore_fifo_pop_blocking();
        memcpy(out, float_as_unsigned_words, sizeof(float));
        return true;
    }
    return false;
}
