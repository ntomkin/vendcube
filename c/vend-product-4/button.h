#include "Arduino.h"

#ifndef Button_h
#define Button_h
class Button {
  public:
    Button(int pin, void (*callback)());
    void (*_callback)();
    void loop();

  private:
    int _pin;
    static Button* instance; 
};
#endif