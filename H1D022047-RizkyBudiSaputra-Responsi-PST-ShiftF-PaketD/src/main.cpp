#include <Arduino.h>
#include <Servo.h>

// Setting Alat. Echo pin dan trigger pin dari Ultrasonik adalah pin digital. LED Juga
int echoPin = D0;
int trigPin = D1;
int redLED = D2;
int greenLED = D3;

// Jarak dan waktu untuk menyimpan hasil dari ultrasonik
long duration;
int distance;

// Servo dan position untuk mengatur pergerakan posisi servo
Servo myServo;
int position;

void setup()
{
  // Echo menerima gelombang suara
  pinMode(echoPin, INPUT);
  // Trigger mengeluarkan gelombang suara
  pinMode(trigPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  myServo.attach(D4);
  Serial.begin(9600);
}

void loop()
{
  // Menggunakan sensor ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  // menghitung jarak
  distance = duration * 0.034 / 2;

  Serial1.print("Distance : ");
  Serial1.print(distance);
  Serial1.print(" cm");

  if (distance <= 150)
  // Ada hewan dalam jarak 1,5 meter
  {
    digitalWrite(greenLED, HIGH);
    // Membuka gerbang
    if (position <= 0)
    {
      position = 180;
      myServo.write(position);
      delay(10);
    }
  }
  else // tidak ada hewan dalam jarak 1,5 meter
  {
    digitalWrite(redLED, HIGH);
    // Menutup gerbang
    if (position <= 180)
    {
      position = 0;
      myServo.write(position);
      delay(10);
    }
  }
}
