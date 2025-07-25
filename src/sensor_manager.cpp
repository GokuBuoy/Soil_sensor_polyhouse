#include "sensor_manager.h"
#include "config.h"

// Sensor reading + smoothing logic
bool readAndProcessSensorData(ModbusMaster &node) {
  uint8_t result = node.readHoldingRegisters(0x0000, 8);

  if (result == node.ku8MBSuccess) {
    for (int i = 0; i < 8; i++) {
      sensorData[i] = node.getResponseBuffer(i);
    }

    // Process temperature
    int16_t rawTemp = sensorData[0];
    currentTemp = (rawTemp > 1000) ? -(6553.6 - rawTemp / 10.0) : rawTemp / 10.0;

    // Process moisture
    currentMoisture = sensorData[1] / 10.0;

    // Store in history buffer
    tempHistory[historyIndex] = currentTemp;
    moistureHistory[historyIndex] = currentMoisture;
    historyIndex = (historyIndex + 1) % SMOOTHING_SAMPLES;

    // Debug
    Serial.print("\n[");
    Serial.print(millis() / 1000);
    Serial.println("s] Sensor Readings:");
    Serial.println("----------------");
    Serial.print("Temperature: "); Serial.print(currentTemp, 1); Serial.println("°C");
    Serial.print("Moisture:    "); Serial.print(currentMoisture, 1); Serial.println("%");
    Serial.print("Location:    "); Serial.println(location);
    Serial.println("----------------");
    Serial.print("Salinity:    "); Serial.print(sensorData[2]); Serial.println(" μS/cm");
    Serial.print("Conductivity:"); Serial.print(sensorData[3]); Serial.println(" μS/cm");
    Serial.print("pH:          "); Serial.print(sensorData[4] / 100.0, 2); Serial.println("");
    Serial.print("N-P-K:       "); Serial.print(sensorData[5]); Serial.print("-");
    Serial.print(sensorData[6]); Serial.print("-"); Serial.println(sensorData[7]);

    return true;
  } else {
    Serial.print("Modbus error: 0x");
    Serial.println(result, HEX);
    return false;
  }
}

void setupModbus(ModbusMaster &node) {
  node.begin(SENSOR_ADDRESS, Serial2);
  node.preTransmission([]() {
    digitalWrite(MAX485_DE_RE, HIGH);
    delayMicroseconds(500);
  });
  node.postTransmission([]() {
    delayMicroseconds(500);
    digitalWrite(MAX485_DE_RE, LOW);
  });
}