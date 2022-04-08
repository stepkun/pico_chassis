
#!/bin/sh

INSTALL_BASE=$HOME/pico

echo "Updating pico SDK's in $INSTALL_BASE"

# pico sdk:
cd $INSTALL_BASE/pico-sdk
git pull
git submodule update

# micro-ros sdk for pico:
cd $INSTALL_BASE/micro_ros_raspberrypi_pico_sdk
git pull
git submodule update

# OpenOCD if installed
if [ -d $INSTALL_BASE/openocd ]
    then
        cd $INSTALL_BASE/openocd
        git pull
        cd openocd
        make -j3
fi
