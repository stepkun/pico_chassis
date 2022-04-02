#ifndef encoder_h
#define encoder_h

#include <pico/stdlib.h>

/**
 * @brief Class "Encoder" 
 * 
 */
class NonDirectionalEncoder
{
    public:
        /**
         * @brief Initialize the Non Directional Encoder class
         * 
         * @param sample_time_ms 
         * @param encoder_holes 
         */
        static void init_class(int sample_time_ms, uint8_t encoder_holes);

        /**
         * @brief Construct a new Non Directional Encoder object
         * 
         */
        NonDirectionalEncoder();

        /**
         * @brief Initialize the Non Directional Encoder object
         * 
         */
        void init(uint8_t interrupt_pin);

        /**
         * @brief Get the current rpm value
         * 
         * @return float - current rpm
         */
        inline float get_rpm(){ return _current_rpm; };

    private:
        float _current_rpm;
        uint _ticks;

        friend void encoder_interrupt_callback(uint device, uint32_t events);
        friend bool encoder_timer_callback(repeating_timer_t *rt);
};

#endif