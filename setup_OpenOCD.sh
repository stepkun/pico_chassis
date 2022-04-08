
#!/bin/sh

INSTALL_BASE=$HOME/pico

echo "Installing OpenOCD in $INSTALL_BASE"

sudo apt install automake autoconf build-essential texinfo libtool libftdi-dev libusb-1.0-0-dev -y

if [ -d $INSTALL_BASE ]
then
    if [ -d $INSTALL_BASE/openocd ]
    then
        echo "Error: OpenOCD already intalled." 
        echo "To reinstall remove directory $INSTALL_BASE/openocd ." 
    else
        cd $INSTALL_BASE
        git clone https://github.com/raspberrypi/openocd.git --recursive --branch rp2040 --depth=1
        cd openocd
        ./bootstrap
        ./configure --enable-ftdi --enable-sysfsgpio --enable-bcm2835gpio
        make -j3
        sudo make install
    fi
else
    echo "Error: You need to install pico-sdk first." 
    echo "Run 'setup-micro-ros-pico-sdk.sh' first"
fi