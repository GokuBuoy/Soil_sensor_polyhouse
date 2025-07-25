#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include "wifi_manager.h"
#include "config.h"

// LCD instance (externally declared in main or managed globally if needed)
extern LiquidCrystal_I2C lcd;

// Track last WiFi check time
unsigned long lastWiFiCheck = 0;

void setupWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  lcd.clear();
  lcd.print("Connecting WiFi");

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    lcd.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    lcd.clear();
    lcd.print("WiFi Connected");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
    delay(2000);
  } else {
    Serial.println("\nFailed to connect!");
    lcd.clear();
    lcd.print("WiFi Failed");
  }
}

void checkWiFiConnection() {
  if (millis() - lastWiFiCheck >= WIFI_RECONNECT_INTERVAL) {
    lastWiFiCheck = millis();

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi disconnected - attempting to reconnect");
      WiFi.disconnect();
      WiFi.reconnect();

      unsigned long startAttemptTime = millis();
      while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 5000) {
        delay(100);
      }

      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Reconnected to WiFi");
      } else {
        Serial.println("Reconnection failed");
      }
    }
  }
}