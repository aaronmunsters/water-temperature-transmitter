#include <Config.h>
#include <cppQueue.h>
#include <Arduino.h>
#include "TsmMeasurement.h"

cppQueue measurements(
    sizeof(SensorMeasurement),
    QUEUE_BUFFER_SIZE,
    LIFO);

cppQueue measurementsHandled(
    sizeof(SensorMeasurement),
    QUEUE_BUFFER_SIZE,
    LIFO);

float getTemperature(SensorMeasurement *measurement)
{
    return static_cast<float>(measurement->temperature) / 10.0f;
}

String measure_as_string(SensorMeasurement *measurement)
{
    String result = "";
    result.concat("{");
    result.concat("\"epoch\":");
    result.concat(measurement->timestamp);
    result.concat(",");
    result.concat("\"measure\":");
    result.concat(getTemperature(measurement));
    result.concat("}");
    return result;
}

String measures_as_string()
{
    SensorMeasurement sensorMeasurement;
    String total = "";

    if (!measurements.isEmpty())
    {
        measurements.pop(&sensorMeasurement);
        total += measure_as_string(&sensorMeasurement);
        measurementsHandled.push(&sensorMeasurement);
    }

    // For as long as the queue contains measurements, add to buffer
    while (!measurements.isEmpty())
    {
        measurements.pop(&sensorMeasurement);
        total += ",";
        total += measure_as_string(&sensorMeasurement);
        measurementsHandled.push(&sensorMeasurement);
    }

    // return all from `measurementsHandled` to `measurements`
    while (!measurementsHandled.isEmpty())
    {
        measurementsHandled.pop(&sensorMeasurement);
        measurements.push(&sensorMeasurement);
    }

    return total;
}

void replyLastMeasures()
{
    String json_body = "";
    json_body.concat("{\"epoch-offset-hours\":");
    json_body.concat(OFFSET_HOURS);
    json_body.concat(",\"lastmeasures\": [");
    json_body.concat(measures_as_string());
    json_body.concat("]}");
    server.send(200, "application/json", json_body);
}
