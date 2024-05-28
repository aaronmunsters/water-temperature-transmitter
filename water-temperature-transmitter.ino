#include "config.h"
#include <SoftwareSerial.h>

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

SoftwareSerial stoveSensorSerial(RX_PIN, TX_PIN);
WiFiServer server(80);

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

void setup() {
  Serial.begin(9600);
  stoveSensorSerial.begin(1200);
  
  // Connect to WiFi
  connectWifi();

  // Start the server
  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (!client) return;

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");


  client.print("Stove data:");

  if (stoveSensorSerial.available()) {
    String data = "";
    while (stoveSensorSerial.available()) {
      char c = stoveSensorSerial.read();
      data += c;
    }
    client.print(data);
  }

  client.println("<br><br>");;  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
