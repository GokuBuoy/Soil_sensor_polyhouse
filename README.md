# 🌱 ESP32 Soil Sensor Monitor for Polyhouse

This is a modular C++ firmware for an ESP32 Dev Module that reads soil sensor data (via Modbus RS485), displays it on an LCD, and uploads the data to a remote server over WiFi.

---

## 🔧 Features

- 📡 **Modbus RS485 Sensor**:
  - Temperature
  - Moisture
  - Salinity
  - Conductivity
  - pH
  - NPK (Nitrogen, Phosphorus, Potassium)

- 🖥️ **LCD Display (16x2 I2C)**:
  - Dual screens: Toggle between Sensor Overview & NPK Data
  - WiFi status + location display

- 🔘 **Buttons**:
  - Screen toggle
  - Multi-click to set `location` (1–6)

- 🌐 **WiFi Upload**:
  - Sends data every 15s to PHP server (`soil_sensor_data.php`)

- 🧠 **Data Smoothing**:
  - Rolling average of last 5 readings for temp & moisture

- ⚙️ **Modular Codebase**:
  - Separated logic for WiFi, LCD, Modbus, Buttons, Server

---

## 📦 Folder Structure


---

## 🔌 Hardware Used

| Component              | Details                                |
|------------------------|----------------------------------------|
| Board                  | ESP32 Dev Module                       |
| Soil Sensor            | Modbus RTU (8 register output)         |
| LCD Display            | 16x2 I2C (Address 0x27)                |
| Buttons                | 2x Momentary (for screen & location)   |
| RS485 Converter        | TTL to RS485 with DE/RE pin on GPIO 4  |
| WiFi                   | Onboard ESP32 WiFi                     |

---

## 🛠️ Wiring (GPIO Pins)

| Function       | GPIO Pin |
|----------------|----------|
| RS485 DE/RE    | 4        |
| Screen Button  | 5        |
| Location Button| 18       |
| RS485 TX       | 17       |
| RS485 RX       | 16       |

---

## 📲 Server Endpoint

Send data every 15 seconds via HTTP GET:


> Update your `config.h` with the real API key and endpoint.

---

## 🧪 Compile & Upload

Make sure you have PlatformIO installed.

```bash
platformio run
platformio upload
platformio device monitor