
#/usr/bin/bash!

# toolchain:
sudo apt update
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib curl wget

cd ~

if [ -d $HOME/pico ]
then
    cd ~/pico
else
    mkdir ~/pico
    cd ~/pico
fi

# pico sdk:
if [ -d $HOME/pico/pico-sdk ]
then
    echo "The pico-sdk is already installed"
    echo "To reinstall remove directory ~/pico/pico-sdk and delete export in ~/.bashrc"
else
    git clone -b master https://github.com/raspberrypi/pico-sdk.git
    cd pico-sdk
    git submodule update --init
    cd ~
    echo 'export PICO_SDK_PATH=~/pico/pico-sdk' >> ~/.bashrc
fi

# only needed if you want to install the examples
#if [ -d $HOME/pico/pico-sdk ]
#then
#    echo "The pico-examples is already installed"
#    echo "To reinstall remove directory ~/pico/pico-examples"
#else
#   cd ~/pico
#   git clone -b master https://github.com/raspberrypi/pico-examples.git
#fi

# micro-ros sdk for pico:
if [ -d $HOME/pico/micro_ros_raspberrypi_pico_sdk ]
then
    echo "The micro-ros pico-sdk is already installed" 
    echo "To reinstall remove directory ~/pico/micro_ros_raspberrypi_pico_sdk and delete export in ~/.bashrc"
else
    cd ~/pico
    git clone git@github.com:micro-ROS/micro_ros_raspberrypi_pico_sdk.git
    cd micro_ros_raspberrypi_pico_sdk
    git submodule update --init
    cd ~
    echo 'export MICRO_ROS_PICO_SDK_PATH=~/pico/micro_ros_raspberrypi_pico_sdk' >> ~/.bashrc
fi
