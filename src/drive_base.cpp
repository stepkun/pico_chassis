//

#include "drive_base.h"
#include "pwm_dual_motor_driver.h"
#include "pwm_controller.h"
#include "non_directional_encoder.h"

// pi currently not in math lib 
#define M_PI 3.14159265358979323846d
// specific definitions
#define F_PI 3.1415926535897932f
#define D_PI 3.141592653589793238462643383279502884d

// create the components
NonDirectionalEncoder left_encoder, right_encoder;
PWMChannel left_channel, right_channel;
PWMController left_controller, right_controller;
PWMDualMotorDriver motor_driver;

DriveBase::DriveBase()
{
    NonDirectionalEncoder::init_class(RPM_CONTROLLER_SAMPLE_TIME_MS, ENCODER_HOLES);
    PWMController::init_class(RPM_CONTROLLER_SAMPLE_TIME_MS);

    _motor_driver = &motor_driver;

    left_encoder.init(LEFT_ENCODER_PIN);
    right_encoder.init(RIGHT_ENCODER_PIN);

    left_channel.init(IN1A, IN2A, PWMA, PWM_RESOLUTION);
    right_channel.init(IN1B, IN2B, PWMB, PWM_RESOLUTION);

    left_controller.init(&left_channel, &left_encoder, PID_KP, PID_KI, PID_KD);
    right_controller.init(&right_channel, &right_encoder, PID_KP, PID_KI, PID_KD);

    motor_driver.init(&left_controller, &right_controller, STBY);
}

// a constant value needed to calculate rpm from velocity
const float SCALE = 60.0f / (WHEEL_DIAMETER * WHEEL_DIAMETER * F_PI);

void DriveBase::set_velocity(float linear, float angular)
{
    // calculate linear and angular parts of rpm
    float speed = 2.0 * linear * SCALE;
    float turn = angular * WHEEL_TRACK * SCALE;

    _motor_driver->set_rpm((speed - turn), (speed + turn));
}
