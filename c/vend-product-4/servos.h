#include "Arduino.h"
#include <ESP32Servo.h>

#ifndef Servos_h
#define Servos_h
class Servos {
  public:
    Servos(byte pin, float rotationInSeconds);
    void rotate(int dir);
    void loop();

  private:
    byte _pin;
    float _rotationInSeconds = 0;
    Servo _servo;
    static Servos* instance; 
};
#endif