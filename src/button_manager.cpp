#include "button_manager.h"
#include "lcd_manager.h"
#include "config.h"

Bounce screenButton = Bounce();
Bounce locationButton = Bounce();
unsigned long lastLocationPressTime = 0;
byte locationPressCount = 0;

void setupButtons() {
  pinMode(BUTTON_PIN_SCREEN, INPUT_PULLUP);
  pinMode(BUTTON_PIN_LOCATION, INPUT_PULLUP);

  screenButton.attach(BUTTON_PIN_SCREEN);
  screenButton.interval(25);

  locationButton.attach(BUTTON_PIN_LOCATION);
  locationButton.interval(25);
}

void handleButtons(LiquidCrystal_I2C &lcd) {
  screenButton.update();
  locationButton.update();

  // Toggle display screen
  if (screenButton.fell()) {
    currentDisplay = (currentDisplay == SCREEN_1) ? SCREEN_2 : SCREEN_1;
    updateLCDDisplay(lcd);
    Serial.print("Screen toggled to: ");
    Serial.println(currentDisplay == SCREEN_1 ? "SCREEN_1" : "SCREEN_2");
  }

  // Multi-press to change location
  if (locationButton.fell()) {
    unsigned long now = millis();
    if (now - lastLocationPressTime > 2000) {
      locationPressCount = 1;
    } else {
      locationPressCount++;
    }
    lastLocationPressTime = now;

    location = (locationPressCount - 1) % 6 + 1;
    updateLCDDisplay(lcd);
    Serial.print("Location set to: ");
    Serial.println(location);
  }
}