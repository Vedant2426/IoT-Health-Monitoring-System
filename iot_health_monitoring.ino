#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "monitor"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include <DHT.h>

// WiFi
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// MAX30102
MAX30105 sensor;

// DHT11
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Buffers
#define BUFFER_SIZE 100
uint32_t irBuffer[BUFFER_SIZE];
uint32_t redBuffer[BUFFER_SIZE];

int32_t spo2;
int32_t heartRate;
int8_t validSPO2;
int8_t validHeartRate;

void setup()
{
  Serial.begin(115200);
  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();

  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  if (!sensor.begin(Wire, I2C_SPEED_FAST))
  {
    lcd.setCursor(0,0);
    lcd.print("MAX30102 ERROR");
    while (1);
  }

  sensor.setup(60, 4, 2, 100, 411, 4096);

  lcd.setCursor(0,0);
  lcd.print("Place Finger");

  for (int i = 0; i < BUFFER_SIZE; i++)
  {
    while (!sensor.available()) {
      sensor.check();
      Blynk.run();
    }
    redBuffer[i] = sensor.getRed();
    irBuffer[i] = sensor.getIR();
    sensor.nextSample();
  }
}

void loop()
{
  Blynk.run();

  for (int i = 25; i < BUFFER_SIZE; i++)
  {
    redBuffer[i - 25] = redBuffer[i];
    irBuffer[i - 25] = irBuffer[i];
  }

  for (int i = BUFFER_SIZE - 25; i < BUFFER_SIZE; i++)
  {
    while (!sensor.available()) {
      sensor.check();
      Blynk.run();
    }

    redBuffer[i] = sensor.getRed();
    irBuffer[i] = sensor.getIR();
    sensor.nextSample();
  }

  maxim_heart_rate_and_oxygen_saturation(
    irBuffer, BUFFER_SIZE,
    redBuffer,
    &spo2, &validSPO2,
    &heartRate, &validHeartRate
  );

  float tempC = dht.readTemperature();

  if (isnan(tempC)) {
    Serial.println("Temp Error");
    return;
  }

  tempC = tempC + 4.0;
  float tempF = (tempC * 9.0 / 5.0) + 32.0;

  long irValue = irBuffer[BUFFER_SIZE - 1];

  lcd.clear();

  if (irValue < 50000)
  {
    lcd.setCursor(0,0);
    lcd.print("No Finger");

    lcd.setCursor(0,1);
    lcd.print("Temp:");
    lcd.print(tempF, 1);
    lcd.print("F");
  }
  else
  {
    if (!validHeartRate || heartRate < 40 || heartRate > 180)
      heartRate = 0;

    if (spo2 > 100) spo2 = 100;
    if (!validSPO2 || spo2 < 80)
      spo2 = 0;

    lcd.setCursor(0,0);
    lcd.print("HR:");
    lcd.print(heartRate);

    lcd.setCursor(8,0);
    lcd.print("SpO2:");
    lcd.print(spo2);

    lcd.setCursor(0,1);
    lcd.print("Temp:");
    lcd.print(tempF, 1);
    lcd.print("F");

    Blynk.virtualWrite(V0, heartRate);
    Blynk.virtualWrite(V1, spo2);
    Blynk.virtualWrite(V2, tempF);
  }
}