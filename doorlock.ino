#include <ArduinoBLE.h>
#include <Servo.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

Servo lockServo;

// BLE
BLEService lockService("180A");
BLEStringCharacteristic passwordChar("2A57", BLEWrite, 20);

// Password
String password = "1234";

// Pins
const int servoPin = 10;
const int buzzerPin = 11;

// Security
int wrongAttempts = 0;
bool systemLocked = false;

unsigned long lockStartTime = 0;
const unsigned long lockDuration = 30000; // 30 sec

// --------------------------------
// OLED Message Function
// --------------------------------
void showMessage(String line1, String line2)
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,10);
  display.println(line1);

  display.setCursor(0,35);
  display.println(line2);

  display.display();
}

// --------------------------------
// Setup
// --------------------------------
void setup()
{
  Serial.begin(9600);

  // OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    while(true);
  }

  showMessage("DOOR", "LOCK");
  delay(2000);

  showMessage("Waiting", "Password");

  // Servo
  lockServo.attach(servoPin);
  lockServo.write(0);

  // Buzzer
  pinMode(buzzerPin, OUTPUT);

  // BLE
  if (!BLE.begin())
  {
    showMessage("BLE", "FAILED");
    while (1);
  }

  BLE.setLocalName("DOORLOCK");
  BLE.setAdvertisedService(lockService);

  lockService.addCharacteristic(passwordChar);
  BLE.addService(lockService);

  BLE.advertise();

  Serial.println("Door Lock Ready");
}

// --------------------------------
// Main Loop
// --------------------------------
void loop()
{
  // Lockout Mode
  if(systemLocked)
  {
    unsigned long elapsed = millis() - lockStartTime;

    if(elapsed >= lockDuration)
    {
      systemLocked = false;
      wrongAttempts = 0;

      showMessage("SYSTEM", "READY");

      tone(buzzerPin, 3000, 300);

      delay(2000);

      showMessage("Waiting", "Password");
    }
    else
    {
      int remaining =
        (lockDuration - elapsed) / 1000;

      display.clearDisplay();

      display.setTextSize(2);
      display.setCursor(0,10);
      display.println("WAIT");

      display.setCursor(0,35);
      display.print(remaining);
      display.println(" SEC");

      display.display();
    }

    return;
  }

  BLEDevice central = BLE.central();

  if (central)
  {
    Serial.println("Phone Connected");

    showMessage("PHONE", "CONNECTED");

    while (central.connected())
    {
      if(systemLocked)
        break;

      if (passwordChar.written())
      {
        String entered = passwordChar.value();

        Serial.print("Received: ");
        Serial.println(entered);

        showMessage("PASSWORD", "RECEIVED");

        delay(1000);

        // ------------------------
        // CORRECT PASSWORD
        // ------------------------
        if (entered == password)
        {
          wrongAttempts = 0;

          Serial.println("ACCESS GRANTED");

          showMessage("ACCESS", "GRANTED");

          tone(buzzerPin, 3000, 300);

          delay(1000);

          lockServo.write(90);

          showMessage("DOOR", "OPEN");

          delay(5000);

          lockServo.write(0);

          showMessage("DOOR", "LOCKED");

          delay(2000);

          showMessage("Waiting", "Password");
        }

        // ------------------------
        // WRONG PASSWORD
        // ------------------------
        else
        {
          wrongAttempts++;

          Serial.print("Wrong Attempts: ");
          Serial.println(wrongAttempts);

          showMessage("ACCESS", "DENIED");

          tone(buzzerPin, 1000, 300);
          delay(400);
          tone(buzzerPin, 1000, 300);

          delay(1500);

          if(wrongAttempts >= 3)
          {
            Serial.println("SYSTEM LOCKED");

            showMessage("SYSTEM", "LOCKED");

            for(int i=0;i<5;i++)
            {
              tone(buzzerPin, 2000, 200);
              delay(300);
            }

            systemLocked = true;
            lockStartTime = millis();
          }
          else
          {
            display.clearDisplay();

            display.setTextSize(2);

            display.setCursor(0,10);
            display.println("ATTEMPT");

            display.setCursor(0,35);
            display.print(wrongAttempts);

            display.display();

            delay(2000);

            showMessage("Waiting", "Password");
          }
        }
      }
    }

    Serial.println("Phone Disconnected");

    if(!systemLocked)
    {
      showMessage("PHONE", "OFFLINE");

      delay(1000);

      showMessage("Waiting", "Password");
    }
  }
}