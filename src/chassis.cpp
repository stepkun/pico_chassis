#include <stdio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rcl/error_handling.h>

#include <rmw_microros/rmw_microros.h>

#include <geometry_msgs/msg/twist.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>

#include "pico_uart_transports.h"
#include "pico_multicore_fifos.h"
#include "pico_core1_alarm_pool.h"

#include "config.h"
#include "drive_base.h"


// use internal LED for signaling "ready"
#define LED_PIN 25
#define TIMEOUT_MS 1000


//===================================================
// second core stuff
// run DriveBase & Sensors on second core
//===================================================
DriveBase base; // = DriveBase();

void core1_entry()
{
    float linear = 0.0f, angular = 0.0f;
    while(true)
    {
        // wait a short time to see whether we have new velocity data
        if(receive_float_timeout_us(1000*100, &linear))
            angular = receive_float();
        
        base.set_velocity(linear, angular);
    }
}

//===================================================
// ROS stuff
// Run ROS on first core
//===================================================
const char * name_space = "chassis";
const char * node_name = "chassis";
const unsigned int publishing_interval_ms = 1000;

//-----------------------------------------------------
// Subscription topic "/chassis/cmd_vel"
//-----------------------------------------------------
const char * cmd_vel_topic_name = "/chassis/cmd_vel";

rcl_subscription_t cmd_vel_subscriber;

geometry_msgs__msg__Twist cmd_vel_msg;

const rosidl_message_type_support_t * cmd_vel_support = 
                    ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist);

void cmd_vel_callback(const void * msgin)
{
     uint32_t double_as_unsigned_words[4];

   // Cast received message to used type
    const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;

    // Process message
    send_float(msg->linear.x);
    send_float(msg->angular.z);
}

//-----------------------------------------------------
// Helper for cretion and deletion
//-----------------------------------------------------
bool micro_ros_init_successful;
rcl_allocator_t allocator;
rclc_support_t support;
rcl_node_t node;
rclc_executor_t executor;

void create_entities()
{
    rclc_support_init(&support, 0, NULL, &allocator);

    rclc_node_init_default(&node, node_name, name_space, &support);

    // cmd_vel subscriber
    cmd_vel_subscriber = rcl_get_zero_initialized_subscription();
    rclc_subscription_init_default(
        &cmd_vel_subscriber, 
        &node,
        cmd_vel_support, 
        cmd_vel_topic_name
    );

    executor = rclc_executor_get_zero_initialized_executor();

    // IMPORTANT: Adjust num_handles to the amount of (publisher-) timers and subscriptions that you add
    unsigned int num_handles = 1;
    rclc_executor_init(&executor, &support.context, num_handles, &allocator);
    
    // add cmd_vel subscription to the executor
    rclc_executor_add_subscription(
        &executor, 
        &cmd_vel_subscriber, 
        &cmd_vel_msg,
        cmd_vel_callback,
        ON_NEW_DATA
    );

    micro_ros_init_successful = true;
    gpio_put(LED_PIN, true);
}

void destroy_entities()
{
    rcl_ret_t rc;
    // destroy cmd_vel subscribtion
    rc += rcl_subscription_fini(&cmd_vel_subscriber, &node);
    // destroy node 
    rc += rcl_node_fini(&node);
    // destroy executor
    rc += rclc_executor_fini(&executor);
    // destroy support
	rc += rclc_support_fini(&support);

    micro_ros_init_successful = false;
    gpio_put(LED_PIN, false);
}

//===================================================
// main
//===================================================

int main()
{
    const int delay_ms = 1000;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, false);
    sleep_ms(delay_ms);

    // start second core
    multicore_launch_core1(core1_entry);
    sleep_ms(delay_ms);

    // enable serial communication
    rmw_uros_set_custom_transport(
		true,
		NULL,
		pico_serial_transport_open,
		pico_serial_transport_close,
		pico_serial_transport_write,
		pico_serial_transport_read
	);
    sleep_ms(delay_ms);

    micro_ros_init_successful = false;

    allocator = rcl_get_default_allocator();

    // run ROS loop
    const int timeout_ms = 50; 
    const uint8_t attempts = 2;
    const int looptime_ns = RCL_MS_TO_NS(100);
    while(true)
    {
        if(RMW_RET_OK == rmw_uros_ping_agent(timeout_ms, attempts))
        {
            if(!micro_ros_init_successful)
            {
                create_entities();
            } 
            else 
            {
                rclc_executor_spin_some(&executor, looptime_ns);
            }
        }
        else if(micro_ros_init_successful)
        {
            destroy_entities();
        }
    }
    
    return 0;
}