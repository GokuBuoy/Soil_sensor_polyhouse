#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <ModbusMaster.h>

void setupModbus(ModbusMaster &node);
bool readAndProcessSensorData(ModbusMaster &node);

#endif