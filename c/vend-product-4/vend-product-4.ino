#include "coin.h"
#include "servos.h"
// #include "screen.h"
#include "button.h"
#include "config.h"

bool isSystemMode;
int currentScreen = -1;
int nextScreen = 1;
int currentProduct = -1;
float currentProductPrice = 0.00;
unsigned int currentProductColor;
String currentProductTitle1;
String currentProductTitle2;
float credit = 0.00;
int lastInteraction = millis();

//  Product Servos
Servos product1Servo = Servos(PRODUCT_1_MOTOR_PIN, PRODUCT_1_ROTATION);
Servos product2Servo = Servos(PRODUCT_2_MOTOR_PIN, PRODUCT_2_ROTATION);
Servos product3Servo = Servos(PRODUCT_3_MOTOR_PIN, PRODUCT_3_ROTATION);
Servos product4Servo = Servos(PRODUCT_4_MOTOR_PIN, PRODUCT_4_ROTATION);
Servos slideDoor = Servos(SLIDE_MOTOR_PIN, SLIDE_ROTATION);
Servos doorLock = Servos(LOCK_MOTOR_PIN, LOCK_ROTATION);

//  Screen
// Screen screen = Screen();

//  Events
void product1Selected() {
  Serial.println("Product 1 selected");

  if(isSystemMode) {
    product1Servo.rotate(STOCK);
    return;
  }

  if(currentScreen == SCREEN_PRODUCTS) {
    currentProduct = 1;
    currentProductColor = PRODUCT_1_COLOR;
    currentProductPrice = PRODUCT_1_PRICE;
    currentProductTitle1 = PRODUCT_1_TITLE_1;
    currentProductTitle2 = PRODUCT_1_TITLE_2;
    currentScreen = SCREEN_NONE;
    nextScreen = SCREEN_PRODUCT;
  }

  lastInteraction = millis();

}

void product2Selected() {
  Serial.println("Product 2 selected");

  if(isSystemMode) {
    product2Servo.rotate(STOCK);
    return;
  }

  if(currentScreen == SCREEN_PRODUCTS) {
    currentProduct = 2;
    currentProductColor = PRODUCT_2_COLOR;
    currentProductPrice = PRODUCT_2_PRICE;
    currentProductTitle1 = PRODUCT_2_TITLE_1;
    currentProductTitle2 = PRODUCT_2_TITLE_2;
    currentScreen = SCREEN_NONE;
    nextScreen = SCREEN_PRODUCT;
  }

  lastInteraction = millis();

}

void product3Selected() {
  Serial.println("Product 3 selected");

  if(isSystemMode) {
    product3Servo.rotate(STOCK);
    return;
  }

  //  Used as a back button on PRODUCT screen
  if(currentScreen == SCREEN_PRODUCT) {
    currentScreen = SCREEN_NONE;
    nextScreen = SCREEN_PRODUCTS;
    return;
  }

  if(currentScreen == SCREEN_PRODUCTS) {
    currentProduct = 3;
    currentProductColor = PRODUCT_3_COLOR;
    currentProductPrice = PRODUCT_3_PRICE;    
    currentProductTitle1 = PRODUCT_3_TITLE_1;
    currentProductTitle2 = PRODUCT_3_TITLE_2;
    currentScreen = SCREEN_NONE;
    nextScreen = SCREEN_PRODUCT;
  }

  lastInteraction = millis();
}

void product4Selected() {
  Serial.println("Product 4 selected");

  if(isSystemMode) {
    product4Servo.rotate(STOCK);
    return;
  }
  
  if(currentScreen == SCREEN_PRODUCTS) {
    currentProduct = 4;
    currentProductColor = PRODUCT_4_COLOR;
    currentProductPrice = PRODUCT_4_PRICE;
    currentProductTitle1 = PRODUCT_4_TITLE_1;
    currentProductTitle2 = PRODUCT_4_TITLE_2;
    currentScreen = SCREEN_NONE;
    nextScreen = SCREEN_PRODUCT;
  }

  lastInteraction = millis();

}

void coinInserted(float c) {
  Serial.println("Coin inserted at " + String(currentScreen));

  credit = credit + c;

  //screen.updateCredit(currentScreen, currentProductColor, credit);

  lastInteraction = millis();
}

void systemModeSelected() {
  isSystemMode = true;

  lastInteraction = millis();
}

void systemStepSelected() {
  
  if(isSystemMode) {
    //  unlock logic
  } else {
    credit = credit + 0.25;
    delay(250);
  }

  lastInteraction = millis();

}

//  Product Buttons
Button product1Button = Button(PRODUCT_1_BUTTON_PIN, product1Selected);
Button product2Button = Button(PRODUCT_2_BUTTON_PIN, product2Selected);
Button product3Button = Button(PRODUCT_3_BUTTON_PIN, product3Selected);
Button product4Button = Button(PRODUCT_4_BUTTON_PIN, product4Selected);
Button systemModeButton = Button(SYSTEM_MODE_BUTTON_PIN, systemModeSelected);
Button systemStepButton = Button(SYSTEM_STEP_BUTTON_PIN, systemStepSelected);

//  Coin acceptor
Coin coin = Coin(COIN_PIN, coinInserted);

//  Loop
void loop() {
  isSystemMode = false;

  coin.loop();

  systemModeButton.loop();
  systemStepButton.loop();

  product1Button.loop();
  product2Button.loop();
  product3Button.loop();
  product4Button.loop();

  if(isSystemMode) {

    if(currentScreen != SCREEN_SYSTEM_MODE) {

      Serial.println("System Mode Activated!");
      currentScreen = SCREEN_SYSTEM_MODE;
      //screen.system();

    }

  } else {

    if(currentScreen != SCREEN_PRODUCTS and nextScreen == SCREEN_PRODUCTS) {
      currentScreen = SCREEN_PRODUCTS;
      //screen.products();
    }

    if(currentScreen != SCREEN_PRODUCT and nextScreen == SCREEN_PRODUCT) {
      currentScreen = SCREEN_PRODUCT;
      //screen.product(currentProduct, credit);
    }

    if(currentScreen == SCREEN_PRODUCT and credit >= currentProductPrice) {
      currentScreen = SCREEN_VENDING;
      nextScreen = SCREEN_VENDING;

      credit = credit - currentProductPrice;
      //screen.updateCredit(currentScreen, currentProductColor, credit);

      slideDoor.rotate(OPEN);
      delay(100);

      //screen.vend(currentProductTitle1, currentProductTitle2);

      switch(currentProduct) {
        case 1:
          product1Servo.rotate(DISPENSE);
          break;
        case 2:
          product2Servo.rotate(DISPENSE);
          break;
        case 3:
          product3Servo.rotate(DISPENSE);
          break;
        case 4:
          product4Servo.rotate(DISPENSE);
          break;
      }

      delay(1000);
      slideDoor.rotate(CLOSE);

      currentProduct = -1;
      currentProductPrice = 0.00;
      currentProductColor = NULL;

      delay(1000);

      nextScreen = SCREEN_PRODUCTS;
    }
    
  }

  // if(millis() - lastInteraction > WAIT_BEFORE_RESET_STATE_MILLISECONDS and currentProduct > 0) {

  //   currentProduct = 0;
  //   currentProductPrice = 0.00;
  //   currentProductColor = NULL;
  //   nextScreen = SCREEN_PRODUCTS;
  //   lastInteraction = millis();

  // }

//  screen.updateCredit(currentScreen, currentProductColor, credit);
}

void setup() {
  Serial.begin(9600);

  doorLock.rotate(LOCK);
  //slideDoor.rotate(CLOSE);

  //screen.setup();
}

