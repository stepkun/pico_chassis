cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

###############################################
## Micro-ROS pico-hassis                     ##
###############################################
project(pico-chassis C CXX ASM)

pico_sdk_init()

link_directories($ENV{MICRO_ROS_PICO_SDK_PATH}/libmicroros)

add_executable(${PROJECT_NAME}
    src/chassis.cpp
    # pico specific commons
    src/pico_uart_transports.c
    src/pico_multicore_fifos.c
    src/pico_interrupts.c
    src/pico_core1_alarm_pool.c
    # drive base
    src/drive_base.cpp
    src/pwm_dual_motor_driver.cpp
    src/pwm_controller.cpp
    src/pwm_channel.cpp
    src/non_directional_encoder.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
    $ENV{MICRO_ROS_PICO_SDK_PATH}/libmicroros/include
)

target_link_libraries(${PROJECT_NAME}
    microros
    pico_stdlib
    pico_multicore
    hardware_gpio
    hardware_pwm
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS YES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Configure Pico
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC PICO_UART_ENABLE_CRLF_SUPPORT=0
    PUBLIC PICO_STDIO_ENABLE_CRLF_SUPPORT=0
    PUBLIC PICO_STDIO_DEFAULT_CRLF=0
    PUBLIC PICO_DEFAULT_I2C=1
)

# Generate UF2
pico_add_extra_outputs(${PROJECT_NAME})

install(CODE "execute_process(COMMAND sh ${PROJECT_SOURCE_DIR}/install_uf2.sh)")

# and still have to handle AMENT_CMAKE_SYMLINK_INSTALL warning
