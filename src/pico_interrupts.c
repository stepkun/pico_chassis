
#include "pico_interrupts.h"

#include <hardware/sync.h>

// we have to initialize interrupt handler for both cores
bool is_initialized[2] = { false, false };

// pi pico has 30 gpio pins
#define NUM_INTS 30
// storage for the function pointers to callbacks
gpio_irq_callback_t callbacks[NUM_INTS];
// storage for the device identifier
uint8_t devices[NUM_INTS];

// internal interrupt-handler, just calls the appropriate registered handler
void interrupt_callback(uint gpio, uint32_t events)
{
    callbacks[gpio](devices[gpio], events);
}

gpio_irq_callback_t register_interrupt(uint8_t gpio, uint32_t events, gpio_irq_callback_t callback, uint8_t device)
{
    assert(gpio >= 0);
    assert(gpio < NUM_INTS);

    devices[gpio] = device;

    if(is_initialized[get_core_num()])
    {
        // remember prevoius callback
        gpio_irq_callback_t ptr = callbacks[gpio];
        callbacks[gpio] = callback;
        // enable additional gpio for interrupts
        gpio_set_irq_enabled(
            gpio,
            events,
            true
        );

        return ptr;
    }
    else
    {
        // initilize interrupts for this core
        is_initialized[get_core_num()] = true;

        callbacks[gpio] = callback;

        // enable gpio for interrupt and register internal interrupt handler
        gpio_set_irq_enabled_with_callback(
            gpio,
            events,
            true,
            &interrupt_callback
        );
        
        return NULL;
    }
}