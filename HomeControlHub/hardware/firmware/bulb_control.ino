#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Function Prototypes
void setupHardware();
void wifiConnection();
void fetchAndControlBulb();
void controlBulb(bool state);

// Wi-Fi Credentials
const char* ssid = "ASlAM 018 2.4G";          // Replace with your Wi-Fi SSID
const char* password = "birmingham@999";      // Replace with your Wi-Fi password

// Server URL
const char* serverUrl = "http://192.168.100.37:8080/bulb"; // Node.js server URL

// GPIO Pin Definition
#define BULB_PIN 2 // GPIO2 (D4)

void setup() {
  setupHardware();
  wifiConnection();
}

void loop() {
  fetchAndControlBulb(); // Continuously fetch and process data in real time
}

/**
 * @brief Sets up the hardware components.
 */
void setupHardware() {
  Serial.begin(115200);
  pinMode(BULB_PIN, OUTPUT);   // Set D4 as output for the bulb
  digitalWrite(BULB_PIN, LOW); // Initialize bulb as OFF
  Serial.println("Hardware initialized");
}

/**
 * @brief Establishes Wi-Fi connection.
 */
void wifiConnection() {
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

/**
 * @brief Fetches bulb status from the server and controls the bulb.
 */
void fetchAndControlBulb() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    Serial.println("Sending GET request to server...");
    http.begin(client, serverUrl);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String response = http.getString();
      Serial.println("Server Response: " + response);

      // Parse bulb status and control it
      if (response.indexOf("\"bulbStatus\":true") != -1) {
        controlBulb(true);  // Turn bulb ON
      } else if (response.indexOf("\"bulbStatus\":false") != -1) {
        controlBulb(false); // Turn bulb OFF
      } else {
        Serial.println("Invalid response format");
      }
    } else {
      Serial.println("Error in GET request: " + String(httpCode));
    }

    http.end();
  } else {
    Serial.println("Wi-Fi not connected. Reconnecting...");
    wifiConnection(); // Attempt to reconnect if Wi-Fi is lost
  }
}

/**
 * @brief Controls the bulb by turning it ON or OFF.
 * 
 * @param state Boolean indicating ON (true) or OFF (false) state.
 */
void controlBulb(bool state) {
  if (state) {
    digitalWrite(BULB_PIN, LOW); // Turn bulb ON
    Serial.println("Bulb ON");
  } else {
    digitalWrite(BULB_PIN, HIGH); // Turn bulb OFF
    Serial.println("Bulb OFF");
  }
}