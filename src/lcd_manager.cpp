#include "lcd_manager.h"
#include "config.h"
#include <WiFi.h>

DisplayState currentDisplay = SCREEN_1;

void setupLCD(LiquidCrystal_I2C &lcd) {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Starting");
  lcd.setCursor(0, 1);
  lcd.print("Loc:1 Wait...");
}

void updateLCDDisplay(LiquidCrystal_I2C &lcd) {
  lcd.clear();

  if (currentDisplay == SCREEN_1) {
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(tempHistory[(historyIndex - 1 + SMOOTHING_SAMPLES) % SMOOTHING_SAMPLES], 1);
    lcd.print((char)223);
    lcd.print("C H:");
    lcd.print(moistureHistory[(historyIndex - 1 + SMOOTHING_SAMPLES) % SMOOTHING_SAMPLES], 1);
    lcd.print("%");

    lcd.setCursor(15, 0);
    lcd.print(WiFi.status() == WL_CONNECTED ? "Y" : "N");

    lcd.setCursor(0, 1);
    lcd.print("S:");
    lcd.print(sensorData[2]);
    lcd.print(" pH:");
    lcd.print(sensorData[4] / 100.0, 1);
    lcd.print(" L:");
    lcd.print(location);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Cond:");
    lcd.print(sensorData[3]);
    lcd.print("uS/cm");

    lcd.setCursor(0, 1);
    lcd.print("NPK:");
    lcd.print(sensorData[5]);
    lcd.print("-");
    lcd.print(sensorData[6]);
    lcd.print("-");
    lcd.print(sensorData[7]);
    lcd.print(" L:");
    lcd.print(location);
  }
}