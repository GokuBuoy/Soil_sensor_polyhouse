
#ifndef CONFIG_H
#define CONFIG_H

// ---------- Pins ----------
#define MAX485_DE_RE          4
#define BUTTON_PIN_SCREEN     5
#define BUTTON_PIN_LOCATION   18

// ---------- Modbus ----------
#define MODBUS_BAUD           9600
#define SENSOR_ADDRESS        1

// ---------- LCD ----------
#define LCD_ADDRESS           0x27

// ---------- Timings ----------
#define LCD_UPDATE_INTERVAL       5000
#define SENSOR_READ_INTERVAL      5000
#define SERVER_UPDATE_INTERVAL    15000
#define WIFI_RECONNECT_INTERVAL   30000
#define BUTTON_DEBOUNCE_TIME      300

// ---------- WiFi ----------
extern const char* ssid;
extern const char* password;

// ---------- Server ----------
extern const char* serverURL;
extern const char* deviceID;
extern const char* apiKey;

// ---------- Data ----------
#define SMOOTHING_SAMPLES     5

extern float tempHistory[SMOOTHING_SAMPLES];
extern float moistureHistory[SMOOTHING_SAMPLES];
extern byte historyIndex;
extern float currentTemp;
extern float currentMoisture;
extern uint16_t sensorData[8];
extern int location;

#endif
