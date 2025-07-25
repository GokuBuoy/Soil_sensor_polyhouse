#include "config.h"
#include "secrets.h"  // 👈 Add this line


// Data storage
float tempHistory[SMOOTHING_SAMPLES] = {0};
float moistureHistory[SMOOTHING_SAMPLES] = {0};
byte historyIndex = 0;
float currentTemp = 0;
float currentMoisture = 0;
uint16_t sensorData[8] = {0};
int location = 1;