# Water Temperature Transmitter
Water Temperature Transmitter for Sensor Attached to Stove

## Setup Instructions

1. Copy the `config.h.example` file to `config.h`:
```sh
cp config.h.example config.h
```

2. Open the `config.h` file and enter your configuration details (e.g., WiFi SSID, WiFi password, ...)

3. Save the file and proceed with uploading the code to your Arduino.

# Libraries used

* [SoftwareSerial Library][software-serial-library]: to communicate with the sensor data.
* [WiFi Library][wifi-library]: to communicate with the local network.
* [Queue Library][queue-library]: to dedicate a queue to write measurements to
* [NTP Library][ntp-library]: to determine the time of a measurement
    * [WifiUDP library][wifiudp-library]: a dependency of NTP Library

# TODO:
- Correctly implement the use of the queue.
    - The queue takes pointers, thus I should allocate them on the heap / preallocate suffucient memory
- Enable OTA updates, perhaps using [ElegantOTA][elegant-ota-documentation]
- Publish events to an MQTT broker, using [MQTT Client][mqtt-client-library]
- Document the [TSM1000][tsm1000-web-page]
   - Document the serial communication interface used to retrieve data (cfr. the [TSM1000 User manual][tsm1000-user-manual], Section 8, pg. 28 & 29)

[software-serial-library]: https://docs.arduino.cc/learn/built-in-libraries/software-serial/
[wifi-library]: https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html
[queue-library]: https://github.com/SMFSW/Queue
[ntp-library]: https://github.com/arduino-libraries/NTPClient
[wifiudp-library]: https://www.arduino.cc/reference/en/libraries/wifi/wifiudp/
[elegant-ota-documentation]: https://elegantota.pro/
[mqtt-client-library]: https://www.arduino.cc/reference/en/libraries/mqtt-client/
[tsm1000-web-page]: https://web.archive.org/web/20240529093135/https://www.h-tronic.de/en/Temperature-Controller-TSM-1000/1114470
[tsm1000-user-manual]: https://web.archive.org/web/20240529091954/https://www.h-tronic.de/media/49/17/ef/1657552422/User%20manual.pdf
