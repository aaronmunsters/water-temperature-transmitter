#include "config.h"
#include <SoftwareSerial.h>
#include <cppQueue.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
#endif

#define OFFSET_TIME_SECONDS (60 * 60 * OFFSET_HOURS) // 60 seconds, 60 minutes
#define JSON_BODY_BUFF_SIZE 1000
#define QUEUE_BUFFER_SIZE 2056
#define MEASURES_AS_STRING_BUFFER_SIZE 1000
#define MEASUREMENT_PRECISION 1

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

WiFiUDP ntpUDP; // Define NTP Client to get time
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", OFFSET_TIME_SECONDS, 60000); // 0 for GMT offset, update interval of 60 seconds


// Storing temperature of *C [-99, 850], stored as [-990, 8500]
// so this fits in a `int16_t` which is [-32768, 32767]
typedef struct sensorMeasurement {
  unsigned long timestamp;
  int16_t temperature;
} SensorMeasurement;

SensorMeasurement fakeMeasures[6] = {
	{ 0x1234, 0x3456 },
	{ 0x5678, 0x7890 },
	{ 0x90AB, 0xABCD },
	{ 0xCDEF, 0xEFDC },
	{ 0xDCBA, 0xBA09 },
	{ 0x0987, 0x8765 }
};

SoftwareSerial stoveSensorSerial(RX_PIN, TX_PIN);
ESP8266WebServer server(80);
cppQueue	measurements(
  sizeof(SensorMeasurement),
  QUEUE_BUFFER_SIZE,
  LIFO
);

cppQueue	measurementsHandled(
  sizeof(SensorMeasurement),
  QUEUE_BUFFER_SIZE,
  LIFO
);

void connectWifi() {
  // Connect to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Connected to WiFi");
  // Print the IP address
  Serial.print("Local IP address: ");
  Serial.print(WiFi.localIP());
  Serial.println();
}

float getTemperature(SensorMeasurement *measurement) {
  return static_cast<float>(measurement->temperature) / 10.0f;
}

String measure_as_string(SensorMeasurement *measurement) {
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

String measures_as_string() {
  SensorMeasurement sensorMeasurement;
  String total = "";
  
  if (!measurements.isEmpty()) {
    measurements.pop(&sensorMeasurement);
    total += measure_as_string(&sensorMeasurement);
    measurementsHandled.push(&sensorMeasurement);
  }

  // For as long as the queue contains measurements, add to buffer
  while (!measurements.isEmpty()) {
    measurements.pop(&sensorMeasurement);
    total += ",";
    total += measure_as_string(&sensorMeasurement);
    measurementsHandled.push(&sensorMeasurement);
  }

  // return all from `measurementsHandled` to `measurements`
  while (! measurementsHandled.isEmpty()) {
    measurementsHandled.pop(&sensorMeasurement);
    measurements.push(&sensorMeasurement);
  }

  return total;
}

void replyLastMeasures() {
  String json_body = "";
  json_body.concat("{\"epoch-offset-hours\":");
  json_body.concat(OFFSET_HOURS);
  json_body.concat(",\"lastmeasures\": [");
  json_body.concat(measures_as_string());
  json_body.concat("]}");
  server.send(200, "application/json", json_body);
}

void checkNewMeasures() {
  if (stoveSensorSerial.available()) {
    String data = "";
    while (stoveSensorSerial.available()) {
      char c = stoveSensorSerial.read();
      data += c;
    }
    // TODO: write to queue
  }

  // TODO:
  // check if there is a new measurement
  // check if this is any different from the previous
  // if so, push to queue

  // time in seconds since Jan. 1, 1970 (+ offset)
  unsigned long epochTime = timeClient.getEpochTime();
}

void setup() {
  stoveSensorSerial.begin(1200);

  // TODO: remove this empty test stuff
  for (unsigned int i = 0 ; i < sizeof(fakeMeasures)/sizeof(SensorMeasurement) ; i++) {
		SensorMeasurement rec = fakeMeasures[i];
		measurements.push(&rec);
	}
  
  // Connect to WiFi
  connectWifi();

  // Start the time client
  timeClient.begin();

  // Define route
  server.on("/", replyLastMeasures);

  // Start the server
  server.begin();
}

void loop() {
  timeClient.update();
  server.handleClient();
  checkNewMeasures();
}
