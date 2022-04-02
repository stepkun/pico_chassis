#ifndef pwm_controller_h
#define pwm_controller_h

#include <pico/stdlib.h>
#include "pwm_channel.h"
#include "non_directional_encoder.h"

/**
 * @brief Class "PWMController" 
 * 
 */
class PWMController
{
    public:
        /**
         * @brief Initialize the PWMController class
         * 
         */
        static void init_class(uint sample_time_ms);

        /**
         * @brief Construct a new PWMController object
         * 
         */
        PWMController();

        /**
         * @brief Initialize the PWMController object
         * 
         * @param channel 
         * @param encoder 
         * @param pid_KP 
         * @param pid_KI 
         * @param pid_KD 
         */

        void init(PWMChannel * channel, NonDirectionalEncoder * encoder, float pid_KP, float pid_KI, float pid_KD);

        /**
         * @brief Set the wanted rpm for PWMController
         * 
         * @param rpm 
         */
        void set_rpm(float rpm) { _rpm_wanted = rpm; };

    private:
        // controller settings
        float _rpm_wanted;
        float _tKP;
        float _tKI;
        float _tKD;
        // Controller "memory"
        float _current_direction;
        int16_t _level;
        // PID "memory"
        float _prev_error;
        float _proportional;
        float _integrator;
        float _differentiator;

        PWMChannel * _channel;
        NonDirectionalEncoder * _encoder;

        friend bool controller_timer_callback(repeating_timer_t *rt);

        /**
         * @brief 
         * 
         */
        void run_pid();
};

#endif