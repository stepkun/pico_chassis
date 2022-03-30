
#/usr/bin/bash!

# toolchain:
sudo apt update
sudo apt upgrade -y

# pico sdk:
cd ~/pico/pico-sdk
git pull
git submodule update

# micro-ros sdk for pico:
cd ~/pico/micro_ros_raspberrypi_pico_sdk
git pull
git submodule update
