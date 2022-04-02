#!/bin/sh
echo "installing pico-chassis.uf2 file on Pi Pico"

if [ -d /media/$USER/RPI-RP2 ]
then
    if [ -d ../../build ]
    then
        cp ../../build/pico-chassis/pico-chassis.uf2 /media/$USER/RPI-RP2
    fi
else
    echo "Pi Pico not found!"
fi
