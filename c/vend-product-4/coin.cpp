#include "Arduino.h"
#include "Coin.h"

Coin::Coin(byte pin, void (*callback)(float c)) {

  _pin = pin;
  _pulseCount = 0;
  _callback = callback;
  setup();

}

void Coin::setup() {
  pinMode(_pin, INPUT_PULLUP);
}

void Coin::loop() {

  if(digitalRead(_pin) == 0) {

    _pulseCount = _pulseCount + 1;
    _lastDetectTime = millis();

  }

  if(_pulseCount > 0 and millis() - _lastDetectTime > 200) {

    determineCredit(_pulseCount);
    _lastDetectTime = 0;
    _pulseCount = 0;

  }

}

void Coin::determineCredit(int pulses) {

  if(pulses > 1000 and pulses < 6000) _callback(0.25);
  if(pulses > 6200 and pulses < 7000) _callback(1.00);
  if(pulses > 10000 and pulses < 14000) _callback(2.00);

}

