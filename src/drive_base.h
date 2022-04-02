#ifndef drive_base_h
#define drive_base_h

// TODO: remove need of configuration file
#include "config.h"
#include "pwm_dual_motor_driver.h"

/**
 * @brief Class "DriveBase" 
 * 
 */
class DriveBase
{
    public:
        /**
         * @brief Construct a new DriveBase object
         */
        DriveBase();

        /**
         * @brief Let the drive base run with a certain speed and turn rate. 
         * 
         * @param linear - speed in m/s, negative values are backwards
         * @param angular - turn rate in rad/s, negative values are clockwise
         */
        void set_velocity(float linear, float angular);

        friend bool check_collision_timer_callback(repeating_timer_t *rt);

    private:
        PWMDualMotorDriver * _motor_driver;
};

#endif