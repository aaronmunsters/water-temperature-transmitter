#include <Arduino.h>
#include "Config.h"
#include <SoftwareSerial.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#endif

#define OFFSET_TIME_SECONDS (60 * 60 * OFFSET_HOURS) // 60 seconds, 60 minutes

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

WiFiUDP ntpUDP;                                                                  // Define NTP Client to get time
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", OFFSET_TIME_SECONDS, 60000); // 0 for GMT offset, update interval of 60 seconds

SoftwareSerial stoveSensorSerial(RX_PIN, TX_PIN);
ESP8266WebServer server(80);

void connectWifi()
{
  // Connect to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Serial.println("Connected to WiFi");
  // Print the IP address
  Serial.print("Local IP address: ");
  Serial.print(WiFi.localIP());
  Serial.println();
}

void checkNewMeasures()
{
  if (stoveSensorSerial.available())
  {
    String data = "";
    while (stoveSensorSerial.available())
    {
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

void replyLastMeasures()
{
  server.send(200, "application/json", "working on it ...");
}

void setup()
{
  stoveSensorSerial.begin(1200);

  // Connect to WiFi
  connectWifi();

  // Start the time client
  timeClient.begin();

  // Define route
  server.on("/", replyLastMeasures);

  // Start the server
  server.begin();
}

void loop()
{
  timeClient.update();
  server.handleClient();
  checkNewMeasures();
}
