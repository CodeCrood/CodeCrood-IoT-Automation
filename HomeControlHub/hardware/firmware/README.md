
# ESP8266 Bulb Control Firmware

This firmware enables an ESP8266-based device to control a bulb (connected to GPIO2) based on the status retrieved from a Node.js server. The device connects to a Wi-Fi network, fetches the bulb status from the server, and controls the bulb accordingly (ON/OFF).

## Features

- Connects to a Wi-Fi network.
- Fetches bulb status (ON/OFF) from a Node.js server.
- Controls a connected bulb using GPIO2 (D4 pin).
- Real-time operation with continuous fetching of data from the server.
  
## Hardware Requirements

- **ESP8266** NodeMCU (or any compatible board).
- **Bulb** connected to GPIO2 (D4 pin) of the ESP8266.
- **Wi-Fi** network for ESP8266 to connect.

## Software Requirements

- **Arduino IDE** with ESP8266 board support.
- **Node.js Server** for managing the bulb state and receiving requests.
  
## Setup

1. **Wi-Fi Credentials**: Replace the `ssid` and `password` variables in the firmware code with your Wi-Fi credentials.

```cpp
const char* ssid = "Your_WiFi_SSID";         // Replace with your Wi-Fi SSID
const char* password = "Your_WiFi_Password"; // Replace with your Wi-Fi password
```

2. **Server URL**: Replace the `serverUrl` with the IP address and port where your Node.js server is running.

```cpp
const char* serverUrl = "http://your-server-ip:8080/bulb";
```

3. **Upload the Firmware**: Upload the code to the ESP8266 using the Arduino IDE.

## How it Works

- The ESP8266 connects to a Wi-Fi network using the provided credentials.
- It continuously sends GET requests to the Node.js server to fetch the bulb status (either ON or OFF).
- Based on the response, the firmware turns the bulb ON or OFF by controlling GPIO2 (D4 pin).
  
- **Response Example**:
  - If the response from the server is `{"bulbStatus":true}`, the bulb will be turned OFF.
  - If the response is `{"bulbStatus":false}`, the bulb will be turned ON.

## Functions

- **wifiConnection()**: Connects the ESP8266 to the Wi-Fi network.
- **fetchAndControlBulb()**: Fetches the bulb status from the Node.js server and controls the bulb accordingly.

## Notes

- The firmware continuously checks the server for updates, so there is no delay introduced between server fetches.
- In case of lost Wi-Fi connection, the device will attempt to reconnect.

