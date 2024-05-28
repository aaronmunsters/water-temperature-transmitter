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

[software-serial-library]: https://docs.arduino.cc/learn/built-in-libraries/software-serial/