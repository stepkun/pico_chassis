//

#include "pwm_dual_motor_driver.h"

#include <hardware/pwm.h>

PWMDualMotorDriver::PWMDualMotorDriver()
{

}

void PWMDualMotorDriver::init(PWMController * controller_A, PWMController * controller_B, uint8_t stby_pin)
{
   _controller_A = controller_A;
   _controller_B = controller_B;
   _stby_pin = stby_pin;

   // init stby pin
   gpio_init(stby_pin);
   gpio_set_dir(stby_pin, GPIO_OUT);
   gpio_put(stby_pin, 1);
}

void PWMDualMotorDriver::set_rpm(int16_t rpm_A, int16_t rpm_B)
{
   _controller_A->set_rpm(rpm_A);
   _controller_B->set_rpm(rpm_B);
}
