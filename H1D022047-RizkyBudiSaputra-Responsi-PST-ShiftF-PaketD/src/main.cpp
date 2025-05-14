#include <Arduino.h>
#include <Servo.h>

int echoPin = D0;
int trigPin = D1;
int redLED = D2;
int greenLED = D3;

long duration;
int distance;

Servo myServo;
int position;

void setup()
{
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  myServo.attach(D4);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial1.print("Distance : ");
  Serial1.print(distance);
  Serial1.print(" cm");

  if (distance <= 150)
  {
    digitalWrite(greenLED, HIGH);
    if (position <= 0)
    {
      position = 180;
      myServo.write(position);
      delay(10);
    }
  }
  else
  {
    digitalWrite(redLED, HIGH);
    if (position <= 180)
    {
      position = 0;
      myServo.write(position);
      delay(10);
    }
  }
}
