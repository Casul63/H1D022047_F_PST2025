#define BLYNK_TEMPLATE_ID "TMPL6QwExwobJ"
#define BLYNK_TEMPLATE_NAME "Multi Purpose Fan"
#define BLYNK_AUTH_TOKEN "KtWpwZC20K1qJ0avSbFhVKVPmDUYoyrf"
#define BLYNK_PRINT Serial

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"

// Variabel Blynk
char auth[] = BLYNK_AUTH_TOKEN;

// Wi-Fi
char ssid[] = "Wokwi-GUEST"; // nama hotspot yang digunakan
char pass[] = "";            // password hotspot yang digunakan

BlynkTimer timer;

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Sensor Udara
const int dhtPin = 15;
DHTesp dhtSensor;

// Sensor Photoresistor
const int ldrPin = 27;

// Ultrasonic sensor
const int trigPin = 26;
const int echoPin = 25;
const int distanceThreshold = 200;

float suhu, duration, distance;
int ldrValue;

void setup()
{
  pinMode(ldrPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    while (1)
      ;
  }
  oled.display();
  delay(2000);

  Blynk.begin(auth, ssid, pass);

  dhtSensor.setup(dhtPin, DHTesp::DHT22);

  timer.setInterval(2000, myEvent);
  oled.clearDisplay();
}

void loop()
{
  ldrValue = analogRead(ldrPin);

  Blynk.run();
  timer.run();

  TempAndHumidity dataDht = dhtSensor.getTempAndHumidity();

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = 0.017 * duration;

  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 2);
  oled.println("Temp : " + String(dataDht.temperature, 2) + "°C"); // set text
  oled.println("Humidity : " + String(dataDht.humidity, 1) + "%");
  oled.println("LDR Value : " + String(ldrValue));

  if (distance <= distanceThreshold && distance > 0)
  {
    oled.println("Terdeteksi Sesuatu");
  }
  else
  {
    oled.println("Tidak Terdeteksi Apapun");
  }

  oled.display();
  delay(2000);
  oled.clearDisplay();
}

void myEvent()
{
  TempAndHumidity dataDht = dhtSensor.getTempAndHumidity();
  suhu = dataDht.temperature;

  Blynk.virtualWrite(V0, suhu);
}