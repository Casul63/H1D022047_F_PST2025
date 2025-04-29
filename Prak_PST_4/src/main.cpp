#include <Arduino.h>
#include <Servo.h>

Servo myServo;

void setup()
{
  myServo.attach(D1);
  Serial.begin(9600);
}

void loop()
{
  for (int pos = 0; pos <= 180; pos++)
  {
    myServo.write(pos);
    delay(10);
  }
  for (int pos = 180; pos >= 0; pos--)
  {
    myServo.write(pos);
    delay(10);
  }
  // myServo.write(90);
  // delay(2000);
  // myServo.write(0);
  // delay(2000);
  // myServo.write(90);
}
