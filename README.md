# 🔐 Bluetooth-Based Smart Door Lock System using Arduino Uno R4 WiFi

A secure Bluetooth Low Energy (BLE) based smart door lock system developed using **Arduino Uno R4 WiFi**, **OLED Display**, **Servo Motor**, and **Buzzer**. The system allows users to unlock a door wirelessly using a smartphone through the **nRF Connect** application.

---

## 📌 Project Overview

This project implements a smart electronic door lock that uses Bluetooth Low Energy (BLE) communication for password authentication. A user enters a password from a smartphone, which is transmitted to the Arduino Uno R4 WiFi. The Arduino verifies the password and controls a servo motor acting as a door lock.

The system also includes:

* OLED display for real-time status monitoring
* Buzzer for audio feedback
* Wrong-attempt monitoring
* Security lockout mechanism after multiple failed attempts

---

## ✨ Features

* 🔵 Bluetooth Low Energy (BLE) authentication
* 🔐 Password-protected door access
* 📱 Smartphone control using nRF Connect
* 📺 OLED status display
* 🔔 Audio alerts using buzzer
* 🚪 Servo motor door locking/unlocking
* 🚫 3-attempt security lockout
* ⏳ 30-second automatic lockout timer
* 💰 Low-cost and easy-to-build system

---

## 🛠 Hardware Components

| Component                        | Quantity    |
| -------------------------------- | ----------- |
| Arduino Uno R4 WiFi              | 1           |
| SSD1306 OLED Display (0.96" I2C) | 1           |
| SG90 Servo Motor                 | 1           |
| Buzzer                           | 1           |
| Breadboard                       | 1           |
| Jumper Wires                     | As Required |
| Smartphone with nRF Connect      | 1           |

---

## 🔌 Circuit Connections

### OLED Display

| OLED Pin | Arduino Uno R4 WiFi |
| -------- | ------------------- |
| VCC      | 5V                  |
| GND      | GND                 |
| SDA      | SDA                 |
| SCL      | SCL                 |

### Servo Motor

| Servo Pin | Arduino Pin |
| --------- | ----------- |
| Signal    | D10         |
| VCC       | 5V          |
| GND       | GND         |

### Buzzer

| Buzzer Pin | Arduino Pin |
| ---------- | ----------- |
| Positive   | D11         |
| Negative   | GND         |

---

## ⚙️ Working Principle

1. Arduino advertises itself as a BLE device named **DOORLOCK**.
2. User connects using the **nRF Connect** mobile application.
3. User sends a password through BLE.
4. Arduino verifies the password.
5. If correct:

   * OLED displays **ACCESS GRANTED**
   * Buzzer gives confirmation beep
   * Servo unlocks the door
6. If incorrect:

   * OLED displays **ACCESS DENIED**
   * Buzzer generates warning sound
   * Wrong-attempt counter increments
7. After 3 incorrect attempts:

   * System enters lockout mode
   * OLED displays countdown timer
   * Further attempts are blocked for 30 seconds

---

## 📱 BLE Communication

### Device Name

```text
DOORLOCK
```

### Characteristic UUID

```text
2A57
```

### Service UUID

```text
180A
```

### Default Password

```text
1234
```

---

## 📺 OLED Display Messages

| Condition         | OLED Message    |
| ----------------- | --------------- |
| Startup           | DOOR LOCK       |
| BLE Ready         | BLE READY       |
| Phone Connected   | PHONE CONNECTED |
| Password Received | PASSWORD CHECK  |
| Correct Password  | ACCESS GRANTED  |
| Wrong Password    | ACCESS DENIED   |
| Door Open         | DOOR OPEN       |
| Door Locked       | DOOR LOCKED     |
| Security Lockout  | SYSTEM LOCKED   |
| Countdown         | WAIT XX SEC     |

---

## 🔒 Security Features

### Wrong Attempt Monitoring

* Tracks incorrect password attempts
* Displays attempt count on OLED

### Lockout Protection

After:

```text
3 Wrong Password Attempts
```

System enters:

```text
SYSTEM LOCKED
```

for:

```text
30 Seconds
```

to prevent brute-force access.

---

## 🧪 Software Simulation

Before implementing Bluetooth communication in hardware, a software simulation was developed using:

* Arduino Uno
* 4×4 Matrix Keypad
* Servo Motor
* Buzzer

The simulation was used only to verify:

* Password authentication logic
* Servo control logic
* Buzzer alert operation

In the final hardware implementation, the keypad was replaced by Bluetooth Low Energy communication to provide a more practical and realistic user interface.

---

## 📊 Project Flow

```text
Smartphone
     │
     ▼
nRF Connect App
     │
     ▼
Bluetooth Low Energy
     │
     ▼
Arduino Uno R4 WiFi
     │
 ┌───┼────┐
 │   │    │
 ▼   ▼    ▼
OLED Servo Buzzer
```

---

## 🚀 Future Improvements

* EEPROM Password Storage
* Password Change Feature
* WiFi Web Dashboard
* GSM OTP Verification
* RFID Authentication
* Fingerprint Authentication
* Mobile Application Development
* IoT Cloud Integration

---

## 📸 Project Demonstration

### Correct Password

```text
ACCESS GRANTED
DOOR OPEN
```

### Wrong Password

```text
ACCESS DENIED
```

### Security Lockout

```text
SYSTEM LOCKED
WAIT 30 SEC
```

---

## 🎯 Applications

* Smart Home Security
* Office Access Control
* Laboratory Security
* Personal Locker Systems
* Educational IoT Projects
* Embedded Systems Demonstrations

---

## 📚 Libraries Used

```cpp
ArduinoBLE
Servo
Wire
Adafruit_GFX
Adafruit_SSD1306
```

---

## 👨‍💻 Author

**Ved Kale**

Electronics Engineering Student
Walchand College of Engineering, Sangli

---

## ⭐ If you like this project

Give this repository a ⭐ and feel free to fork and improve it.
