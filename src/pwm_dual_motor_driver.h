#ifndef pwm_dual_motor_driver_h
#define pwm_dual_motor_driver_h

#include <pico/stdlib.h>
#include "pwm_controller.h"

/**
 * @brief Class "PWMMotorDriver" 
 * 
 */
class PWMDualMotorDriver
{
    public:
        /**
         * @brief Construct a new PWMDualMotorDriver object
         * 
         */
        PWMDualMotorDriver();

        /**
         * @brief Initialize the PWMDualMotorDriver object
         * 
         * @param channel_A
         * @param channel_B
         * @param stby_pin 
         */
        void init(PWMController * controller_A, PWMController * controller_B, uint8_t stby_pin);

        /**
         * @brief Activate the driver
         * 
         */
        void start() { gpio_put(_stby_pin, 1); };

        /**
         * @brief De-activate the driver
         * 
         */
        void stop() { gpio_put(_stby_pin, 0); };

        /**
         * @brief Set the rpm's of both controller
         * 
         * @param rpm_A - left motors to be rpm 
         * @param rpm_B - right motors to be rpm
         */
        void set_rpm(int16_t rpm_A, int16_t rpm_B);

    private:
        PWMController * _controller_A;
        PWMController * _controller_B;
        uint8_t _stby_pin;
};

#endif