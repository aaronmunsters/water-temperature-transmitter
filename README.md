# Water Temperature Transmitter
Water Temperature Transmitter for Sensor Attached to Stove

## Setup Instructions

1. Copy the `config.h.example` file to `config.h`:
```sh
cp config.h.example config.h
```

2. Open the config.h file and enter your WiFi SSID and password:

```cpp
#define WIFI_SSID "your-SSID-here"
#define WIFI_PASSWORD "your-password-here"
```

3. Save the file and proceed with uploading the code to your Arduino.

# Libraries used

* [SoftwareSerial Library][software-serial-library]: to communicate with the sensor data.
* [WiFi Library][wifi-library]: to communicate with the local network.
* [Queue Library][queue-library]: to dedicate a queue to write measurements to
* [NTP Library][ntp-library]: to determine the time of a measurement
    * [WifiUDP library][wifiudp-library]: a dependency of NTP Library

[software-serial-library]: https://docs.arduino.cc/learn/built-in-libraries/software-serial/
[wifi-library]: https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html
[queue-library]: https://github.com/SMFSW/Queue
[ntp-library]: https://github.com/arduino-libraries/NTPClient
[wifiudp-library]: https://www.arduino.cc/reference/en/libraries/wifi/wifiudp/