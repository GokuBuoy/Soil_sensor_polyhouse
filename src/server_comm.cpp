#include <HTTPClient.h>
#include <WiFi.h>
#include "config.h"

void sendDataToServer() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected - skipping server update");
    return;
  }

  HTTPClient http;
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  String url = String(serverURL) + 
               "?temp=" + String(currentTemp, 1) +
               "&moist=" + String(currentMoisture, 1) +
               "&sal=" + String(sensorData[2]) +
               "&cond=" + String(sensorData[3]) +
               "&ph=" + String(sensorData[4] / 100.0, 2) +
               "&n=" + String(sensorData[5]) +
               "&p=" + String(sensorData[6]) +
               "&k=" + String(sensorData[7]) +
               "&location=" + String(location) +
               "&device=" + deviceID +
               "&key=" + apiKey;

  Serial.print("Sending data to server: ");
  Serial.println(url.substring(0, url.indexOf("key=")) + "key=[HIDDEN]");

  http.begin(url);
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println("Server response: " + payload);
  } else {
    Serial.println("Error on HTTP request: " + String(httpCode));
  }

  http.end();
}