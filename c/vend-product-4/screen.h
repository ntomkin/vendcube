#ifndef Screen_h
#define Screen_h
class Screen {
  public:
    Screen();
    void loop();
    void setup();
    void products();
    void product(int productNumber, float credit);
    void vend(String productTitle1, String productTitle2);
    void updateCredit(int currentScreen, unsigned int color, float credit);
    void system();

  private:
    static Screen* instance; 
    float _lastCredit;
    int _lastScreen;
    void renderProduct(int productNumber);
};
#endif