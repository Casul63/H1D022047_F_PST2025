#include <Arduino.h>

// put function declarations here:

int redLED = D0;
int yellowLED = D2;
int greenLED = D3;

void setup()
{
  // put your setup code here, to run once:
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop()
{
  digitalWrite(redLED, HIGH);
  delay(500);
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, HIGH);
  delay(500);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, HIGH);
  delay(500);
  digitalWrite(greenLED, LOW);
}
