#ifndef Coin_h
#define Coin_h
class Coin {
  public:
    volatile float credit;

    Coin(byte pin, void (*callback)(float c));
    void determineCredit(int pulses); 
    void loop();

  private:
    volatile byte _pin;
    void (*_callback)(float c);
    volatile int _pulseCount = 0;
    unsigned long _lastDetectTime = 0;

    void setup();
};
#endif