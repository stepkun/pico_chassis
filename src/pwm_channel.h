#ifndef pwm_channel_h
#define pwm_channel_h

#include <pico/stdlib.h>

/**
 * @brief Class definition for handling of driver channels
 * 
 */
class PWMChannel {
    public:
        /**
         * @brief Construct a new PWMChannel object
         * 
         */
        PWMChannel();
        
        /**
         * @brief Initialize the PWMChannel object
         * 
         * @param in1_pin 
         * @param in2_pin 
         * @param pwm_pin 
         * @param pwm_resolution 
         */
        void init(uint8_t in1_pin, uint8_t in2_pin, uint8_t pwm_pin, uint16_t pwm_resolution);
    
        /**
         * @brief Set the pwm level of channel
         * 
         * Function ensures that the limits of the channel are respected
         * @param level 
         * @return int16_t - the level that was set regarding limits
         */
        int16_t set_level(int16_t level);

    private:
        uint8_t _in1_pin;
        uint8_t _in2_pin;
        uint8_t _pwm_pin;
        uint8_t _pwm_resolution;
        uint8_t _slice;
        uint8_t _channel;
};

#endif