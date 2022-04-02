//
#include "pwm_channel.h"

#include <hardware/pwm.h>

PWMChannel::PWMChannel()
{

}

void PWMChannel::init(uint8_t in1_pin, uint8_t in2_pin, uint8_t pwm_pin, uint16_t pwm_resolution)
{
   _in1_pin = in1_pin;
   _in2_pin = in2_pin;
   _pwm_pin = pwm_pin;
   _pwm_resolution = pwm_resolution;

   // IN1 & IN2 configuration
   gpio_init(_in1_pin);
   gpio_set_dir(_in1_pin, GPIO_OUT);
   gpio_put(_in1_pin, 1);
   gpio_init(_in2_pin);
   gpio_set_dir(_in2_pin, GPIO_OUT);
   gpio_put(_in2_pin, 0);
   // pwm pin configuration with "pwm_resolution" steps
   gpio_set_function(_pwm_pin, GPIO_FUNC_PWM);
   _slice = pwm_gpio_to_slice_num(_pwm_pin);
   _channel = pwm_gpio_to_channel(_pwm_pin);
   pwm_set_wrap(_slice, _pwm_resolution);
   pwm_set_enabled (_slice,  true);
} 

inline int16_t clamp_level(int16_t value, int16_t max)
{
    if(value > max)
        return max;
	else if(value < -max)
        return -max;

    return value;
}

int16_t PWMChannel::set_level(int16_t level)
{
   level = clamp_level(level, _pwm_resolution);

   if(level > 0)
   {
      gpio_put(_in1_pin, 0);
      gpio_put(_in2_pin, 1);
      pwm_set_chan_level (_slice, _channel, level);
   }
   else
   {
      gpio_put(_in1_pin, 1);
      gpio_put(_in2_pin, 0);
      pwm_set_chan_level (_slice, _channel, -level);
   }

   return level;
}
