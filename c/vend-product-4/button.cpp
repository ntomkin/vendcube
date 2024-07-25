#include "Button.h"

Button* Button::instance = nullptr;

Button::Button(int pin, void (*callback)()) {
  _pin = pin;
  _callback = callback;

  pinMode(pin, INPUT_PULLUP);

  Button::instance = this;
}

void Button::loop() {
  if(digitalRead(_pin) == LOW) { 
    _callback();
  }
}