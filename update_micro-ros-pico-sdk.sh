
#/usr/bin/bash!

INSTALL_BASE=$HOME/pico

echo "Updating pico SDK's in $INSTALL_BASE"

# pico sdk:
cd $INSTALL_DIR/pico-sdk
git pull
git submodule update

# micro-ros sdk for pico:
cd $INSTALL_DIR/micro_ros_raspberrypi_pico_sdk
git pull
git submodule update
