#!/bin/sh
echo "installing pico-chassis binary file on Pi Pico"

if [ -d /media/$USER/RPI-RP2 ]
then
    if [ -d ../../build ]
    then
        cp ../../build/pico_chassis/pico_chassis.uf2 /media/$USER/RPI-RP2
    fi
else
    if hash openocd 2>/dev/null;
    then
        openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program ../../build/pico_chassis/pico_chassis.elf verify reset exit"
    else
        echo "Pi Pico not found!"
    fi
fi

