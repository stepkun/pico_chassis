//

#include "pwm_controller.h"
#include "pico_core1_alarm_pool.h"

#ifndef NUM_CONTROLLER
#define NUM_CONTROLLER 2
#endif

// Callback storage 
uint8_t num_controller = 0;
PWMController * controllers[NUM_CONTROLLER];

uint controller_interval_ms;

repeating_timer_t controller_timer;

bool controller_timer_callback(repeating_timer_t *rt)
{
    for(int i = 0; i < num_controller; i++)
    {
        controllers[i]->run_pid();
    }
    return true;
}

void PWMController::init_class(uint sample_time_ms)
{
    controller_interval_ms = sample_time_ms;

    // add repeating timer for controller
    alarm_pool_add_repeating_timer_ms(
        get_core1_alarm_pool(),
        controller_interval_ms,
        controller_timer_callback,
        NULL, &controller_timer
    );
}

PWMController::PWMController()
{

}

void PWMController::init(PWMChannel * channel, NonDirectionalEncoder * encoder, float pid_KP, float pid_KI, float pid_KD)
{
    _channel = channel;
    _encoder = encoder;
    // precalc values to speed up calculation with a scaling of 1/10
    // because we only calculate the change of the input by PID-Controller
    _tKP = 0.1f * pid_KP;
    _tKI = 0.1f * 0.5f * pid_KI * float(controller_interval_ms) / 1000.0f;
    _tKD = 0.1f * 2.0f * pid_KD * 1000.0f / float(controller_interval_ms);

    _rpm_wanted = 0.0f;

    _current_direction = 1.0f;
    _level = 0;
    _prev_error = 0.0f;
    _integrator = 0.0f;
    _differentiator = 0.0f;

    controllers[num_controller] = this;

    num_controller++;
}

inline void PWMController::run_pid()
{
    if(_rpm_wanted == 0.0f)
    {
        _level = 0;
        _prev_error = 0.0f;
        _integrator = 0.0f;
        _differentiator = 0.0f;
    }
    else
    {
        float cur_rpm = _encoder->get_rpm();
        float error = _rpm_wanted - (_current_direction * cur_rpm);
        
        _proportional = _tKP * error;
        _integrator = _integrator + _tKI * (error + _prev_error);
        _differentiator = _tKD * (error - _prev_error);

        // calculate new pwm level
        // the modification compared to a standard PID-Controller is
        // that only the change of the signal is calculated with PID 
        _level = _level + int16_t(_proportional + _integrator + _differentiator);

        // set the direction of rpm encoder
        if(_level > 0) _current_direction = 1.0f;
        else if(_level < 0) _current_direction = -1.0f;
        // if _level == 0 keep direction

        // update controller internal values
        _prev_error = error;
    }
    _level = _channel->set_level(_level);
}

