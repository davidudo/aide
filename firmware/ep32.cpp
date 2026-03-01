#include <WiFiManager.h>
#include <WiFiClient.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

const char* const HOST = "192.168.0.100";
const int PORT = 8080;

WebSocketsClient webSocket;

void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  Serial2.begin(115200);

  bool res = WiFiManager().autoConnect("Aide Robot", "password");

  if (!res) {
    Serial.println("Failed to connect");
  } else {
    Serial.println("Connected to WiFi");
  }

  webSocket.begin(HOST, PORT);
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  if (Serial2.available() > 0) {
    sendJsonData();
  }

  webSocket.loop();
}

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  // Create a JSON object and serialize it
  // StaticJsonDocument<256> doc;
  // doc["sensor_name"] = "sonar";
  // doc["value"] = 255;
  // char jsonStr[256];
  // serializeJson(doc, jsonStr);

  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      webSocket.sendTXT("Connectedz");

      // Send the JSON data to the serial port
      // webSocket.sendTXT(jsonStr);
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] Received text: %.*s\n", length, payload);
      Serial.print("Sending command: ");
      Serial.println((char*)payload);
      Serial2.write(payload, length);
      break;
  }
}

void sendJsonData() {
  int numBytes;
  static char jsonData[256];
  numBytes = Serial2.readBytes(jsonData, sizeof(jsonData) - 1);

  if (numBytes > 0) {
    jsonData[numBytes] = '\0';
    String dataString = String(jsonData);
    Serial.println(dataString);
    webSocket.sendTXT(dataString);
  }
}
