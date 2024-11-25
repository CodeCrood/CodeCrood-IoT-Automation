#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void wifiConnection();
void fetchAndControlBulb();

const char* ssid = "ASlAM 018 2.4G";         // Replace with your Wi-Fi SSID
const char* password = "birmingham@999";     // Replace with your Wi-Fi password

const char* serverUrl = "http://192.168.100.37:8080/bulb"; // Node.js server URL

#define BULB_PIN 2 // GPIO2 (D4)

void setup() {

  Serial.begin(115200);
  pinMode(BULB_PIN, OUTPUT); // Set D4 as output for the bulb
  digitalWrite(BULB_PIN, LOW); // Initialize bulb as OFF
  wifiConnection();
}

void loop() {
  fetchAndControlBulb(); // Continuously fetch and process data in real time
}


void wifiConnection() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}



void fetchAndControlBulb(){
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverUrl);

    int httpCode = http.GET(); // Get bulb status from the server
    if (httpCode > 0) {
      String response = http.getString();
      Serial.println("Server Response: " + response);

      // Check for bulb status (true/false) and control D4 accordingly
      if (response.indexOf("\"bulbStatus\":true") != -1) {
        digitalWrite(BULB_PIN, LOW); // Turn bulb ON
        Serial.println("Bulb OFF");
      } else if (response.indexOf("\"bulbStatus\":false") != -1) {
        digitalWrite(BULB_PIN, HIGH); // Turn bulb OFF
        Serial.println("Bulb ON");
      }
    } else {
      Serial.println("Error in GET request");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
    wifiConnection(); // Reconnect if Wi-Fi is lost
  }
}

