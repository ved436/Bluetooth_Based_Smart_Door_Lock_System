# 🔐 Bluetooth Smart Door Lock System

A Bluetooth-based smart door lock built using **Arduino Uno R4 WiFi**, **OLED Display**, **Servo Motor**, and **Buzzer**. The system allows users to unlock a door wirelessly using the **nRF Connect** mobile application.

## Features

* Bluetooth Low Energy (BLE) Authentication
* Password-Protected Access
* OLED Status Display
* Servo-Based Door Lock
* Buzzer Alerts
* Wrong Attempt Detection
* 30-Second Security Lockout

## Hardware Used

* Arduino Uno R4 WiFi
* SSD1306 OLED Display
* SG90 Servo Motor
* Buzzer
* Smartphone with nRF Connect

## Working

1. Connect to **DOORLOCK** using nRF Connect.
2. Send the password via BLE.
3. Arduino verifies the password.
4. If correct:

   * Door unlocks
   * OLED shows **ACCESS GRANTED**
5. If incorrect:

   * OLED shows **ACCESS DENIED**
   * Wrong attempt counter increases
6. After 3 wrong attempts:

   * System locks for 30 seconds

## Circuit Connections

### OLED

* VCC → 5V
* GND → GND
* SDA → SDA
* SCL → SCL

### Servo

* Signal → D10
* VCC → 5V
* GND → GND

### Buzzer

* Positive → D11
* Negative → GND

## Software Simulation

A 4×4 keypad, servo motor, and buzzer were initially used in simulation to verify the authentication logic. In the final hardware implementation, the keypad was replaced with Bluetooth BLE communication for a more practical and realistic access control system.

## Future Improvements

* EEPROM Password Storage
* Password Change Feature
* WiFi Web Dashboard
* GSM OTP Verification
* RFID Authentication

## Author

**Ved Kale**
Walchand College of Engineering, Sangli
