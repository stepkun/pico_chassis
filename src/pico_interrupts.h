#ifndef pico_interrupts_h
#define pico_interrupts_h

/**
 * @brief An interrupt callback table
 * 
 */

#include <pico/stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Register a (new) interrupt callback
 * 
 * @param pin - GPIO pin for the interrupt
 * @param events - when to trigger the interrupt (High, Low, Rise, Fall, can be combined)
 * @param callback -  address of the interrupt handler to execute
 * @param device - an integer value to identify the device within the callback
 * @return gpio_irq_callback_t - address of replaced callback, NULL if none was registered before
 */
gpio_irq_callback_t register_interrupt(uint8_t pin, uint32_t events, gpio_irq_callback_t callback, uint8_t device);


#ifdef __cplusplus
}
#endif
#endif