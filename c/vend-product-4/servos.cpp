#include "Servos.h"

Servos* Servos::instance = nullptr;

Servos::Servos(byte pin, float rotationInSeconds) {
  _pin = pin;
  _rotationInSeconds = rotationInSeconds * 1000;
  
  Serial.begin(9600);

  Servo _servo;
  Servos::instance = this;
}

void Servos::rotate(int dir) {
  _servo.attach(_pin);

  _servo.writeMicroseconds(2000 * dir);

  delay(_rotationInSeconds);  

  _servo.attach(NULL);
}

