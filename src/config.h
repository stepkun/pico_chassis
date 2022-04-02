#ifndef config_h
#define config_h

// chassis dimensions in m
#define WHEEL_DIAMETER 0.065
#define WHEEL_BASE 0.115
#define WHEEL_TRACK 0.130

// dual channel motor_driver
#define PWM_RESOLUTION 1000
// pin settings for pwm channel's
// left motor = channel A
#define PWMA 22
#define IN2A 21
#define IN1A 20
// "power" pin
#define STBY 19
// right motor = channel B
#define IN1B 18
#define IN2B 17
#define PWMB 16

// pwm_controller
// this is a modified PID controller due to the dead-zone of the motors
// the modification compared to a standard PID-Controller is
// that only the change of the signal is calculated with PID
// @see pwm_controller.cpp 
#define RPM_CONTROLLER_SAMPLE_TIME_MS 33
#define PID_KP 1.2f
#define PID_KI 0.01f
#define PID_KD 0.01f

// encoder
#define ENCODER_HOLES 20
#define LEFT_ENCODER_PIN 14
#define RIGHT_ENCODER_PIN 15

#endif