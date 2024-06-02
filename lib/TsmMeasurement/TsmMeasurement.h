#include <Arduino.h>
#include <Config.h>

#define JSON_BODY_BUFF_SIZE 1000
#define QUEUE_BUFFER_SIZE 2056
#define MEASURES_AS_STRING_BUFFER_SIZE 1000
#define MEASUREMENT_PRECISION 1

// Storing temperature of *C [-99, 850], stored as [-990, 8500]
// so this fits in a `int16_t` which is [-32768, 32767]
typedef struct sensorMeasurement
{
    unsigned long timestamp;
    int16_t temperature;
} SensorMeasurement;
