#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

#include <LiquidCrystal_I2C.h>

enum DisplayState {
  SCREEN_1,
  SCREEN_2
};

extern DisplayState currentDisplay;

void setupLCD(LiquidCrystal_I2C &lcd);
void updateLCDDisplay(LiquidCrystal_I2C &lcd);

#endif