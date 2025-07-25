#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <Bounce2.h>
#include <LiquidCrystal_I2C.h>

extern Bounce screenButton;
extern Bounce locationButton;
extern unsigned long lastLocationPressTime;
extern byte locationPressCount;

void setupButtons();
void handleButtons(LiquidCrystal_I2C &lcd);

#endif