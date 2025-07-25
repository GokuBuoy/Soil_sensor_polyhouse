#include <Arduino.h>
#include <ModbusMaster.h>
#include <LiquidCrystal_I2C.h>
#include "config.h"
#include "wifi_manager.h"
#include "sensor_manager.h"
#include "lcd_manager.h"
#include "button_manager.h"
#include "server_comm.h"

// Create global instances
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
ModbusMaster node;

// Timing trackers
unsigned long startTime;
unsigned long lastLCDUpdate = 0;
unsigned long lastSensorRead = 0;
unsigned long lastServerUpdate = 0;

// Stats
unsigned int successCount = 0;
unsigned int errorCount = 0;
bool systemInitialized = false;

void setup() {
  // Serial for debug
  Serial.begin(115200);
  while (!Serial);

  // RS485 control pin
  pinMode(MAX485_DE_RE, OUTPUT);
  digitalWrite(MAX485_DE_RE, LOW);

  // Init hardware modules
  Serial2.begin(MODBUS_BAUD, SERIAL_8N1, 16, 17);
  setupModbus(node);
  setupButtons();
  setupLCD(lcd);
  setupWiFi();

  startTime = millis();

  Serial.println("\nAdvanced Soil Sensor Monitor");
  Serial.println("===========================");
  Serial.println("System initializing...");
}

void loop() {
  checkWiFiConnection();

  if (!systemInitialized && millis() - startTime >= 5000) {
    systemInitialized = true;
    lcd.clear();
    Serial.println("System ready. Starting measurements...");
  }

  if (!systemInitialized) return;

  // Handle buttons
  handleButtons(lcd);

  // LCD update every 5s
  if (millis() - lastLCDUpdate >= LCD_UPDATE_INTERVAL) {
    lastLCDUpdate = millis();
    updateLCDDisplay(lcd);
  }

  // Sensor reading every 5s
  if (millis() - lastSensorRead >= SENSOR_READ_INTERVAL) {
    lastSensorRead = millis();

    if (readAndProcessSensorData(node)) {
      successCount++;
    } else {
      errorCount++;
      lcd.clear();
      lcd.print("Read Error!");
    }

    // Optional: display stats to serial
    Serial.println("\nSystem Status:");
    Serial.println("--------------");
    Serial.print("Successful readings: "); Serial.println(successCount);
    Serial.print("Failed readings:     "); Serial.println(errorCount);
    Serial.print("Success rate:        ");
    Serial.print((successCount * 100.0) / (successCount + errorCount), 1);
    Serial.println("%");
    Serial.println("===========================");
  }

  // Send to server every 15s
  if (millis() - lastServerUpdate >= SERVER_UPDATE_INTERVAL) {
    lastServerUpdate = millis();

    if (successCount > 0) {
      sendDataToServer();
    }
  }
}