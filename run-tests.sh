#!/usr/bin/env bash

if [ ! -e ~/.platformio/penv/bin/pio ]
then
    echo "Please ensure PlatformIO is installed on your system"
    exit 0
else
    echo "PlatformIO installation found!"
fi

pio=~/.platformio/penv/bin/pio

echo -n '
[env:uno]
platform = atmelavr
framework = arduino
board = uno

; Testing done on simulator
platform_packages =
    platformio/tool-simavr
test_speed = 9600
test_testing_command =
    ${platformio.packages_dir}/tool-simavr/bin/simavr
    -m
    atmega328p
    -f
    16000000L
    ${platformio.build_dir}/${this.__env__}/firmware.elf
' > platformio.ini
LD_LIBRARY_PATH=~/.platformio/packages/tool-simavr/lib \
${pio} test -v --without-uploading

echo -n "; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html
[env:nodemcuv2]
platform = espressif8266
board = nodemcuv2
framework = arduino
lib_deps =
    smfsw/Queue
    arduino-libraries/NTPClient" > platformio.ini
