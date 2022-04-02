// implementation for the non-directional encoder

#include "non_directional_encoder.h"
#include "pico_interrupts.h"
#include "pico_core1_alarm_pool.h"

#ifndef NUM_ENCODER
#define NUM_ENCODER 2
#endif

// Callback storage
uint8_t num_encoders = 0;
NonDirectionalEncoder * encoders[NUM_ENCODER];

int encoder_interval_ms;
float factor;

void encoder_interrupt_callback(uint device, uint32_t events)
{
   encoders[device]->_ticks++;
}

repeating_timer_t encoder_timer;

bool encoder_timer_callback(repeating_timer_t *rt)
{
   for(int i = 0; i < num_encoders; i++)
   {
      encoders[i]->_current_rpm = factor * float(encoders[i]->_ticks);
      encoders[i]->_ticks = 0;
   }
   return true;
}

NonDirectionalEncoder::NonDirectionalEncoder()
{
}

void NonDirectionalEncoder::init(uint8_t interrupt_pin)
{
   // initialize
   _current_rpm = 0.0;
   _ticks = 0;
   encoders[num_encoders] = this;
   // add encoder to interrupt table
   register_interrupt(
      interrupt_pin,
      GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
      &encoder_interrupt_callback,
      num_encoders
   );
   num_encoders++;
}

void NonDirectionalEncoder::init_class(int sample_time_ms, uint8_t encoder_holes)
{
   encoder_interval_ms = sample_time_ms;
   factor = 60000.0f/float(2 * encoder_holes * sample_time_ms);

   // add repeating timer with absolute interval (negative value!)
   alarm_pool_add_repeating_timer_ms(
      get_core1_alarm_pool(),
      -encoder_interval_ms,
      encoder_timer_callback,
      NULL, &encoder_timer);
}
