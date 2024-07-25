#include "Arduino.h"
#include "Screen.h"
#include "Config.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique9pt7b.h>

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

Screen* Screen::instance = nullptr;

Screen::Screen() {

  _lastCredit = 0.00;
  _lastScreen = NULL;
  Screen::instance = this;
}

void Screen::loop() {
}

void Screen::products() {

  String creditText = "CREDIT";
  int creditTextX;
  int creditTextY;
  int creditTextW;
  int creditTextH;

  float creditValue = 0.00;
  int creditValueX;
  int creditValueY;
  int creditValueW;
  int creditValueH;

  tft.fillRect(0, 0, 480, 320, BLACK);

  tft.drawFastHLine(0, SCREEN_HEIGHT/2, SCREEN_HEIGHT*2, WHITE);
  tft.drawFastVLine(SCREEN_WIDTH, 0, SCREEN_HEIGHT, WHITE);

  tft.setCursor(0, 0);
  tft.fillRoundRect(SCREEN_WIDTH-70, (SCREEN_HEIGHT/2)-30, 140, 60, 10, BLACK);
  tft.drawRoundRect(SCREEN_WIDTH-70, (SCREEN_HEIGHT/2)-30, 140, 60, 10, WHITE);

  tft.fillRoundRect(SCREEN_WIDTH-40, (SCREEN_HEIGHT/2)-50, 80, 25, 4, BLACK);
  tft.drawRoundRect(SCREEN_WIDTH-40, (SCREEN_HEIGHT/2)-50, 80, 25, 4, WHITE);

  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  tft.setFont(&FreeSans9pt7b);

  tft.getTextBounds(creditText, SCREEN_WIDTH, (SCREEN_HEIGHT/2), &creditTextX, &creditTextY, &creditTextW, &creditTextH);
  tft.setCursor(creditTextX - (creditTextW/2)-1, creditTextY - (creditTextH/2) - 15);
  tft.println(creditText);

  tft.setTextSize(2);
  tft.getTextBounds(String("$" + String(creditValue)), SCREEN_WIDTH, (SCREEN_HEIGHT/2), &creditValueX, &creditValueY, &creditValueW, &creditValueH);
  tft.setCursor(creditValueX - (creditValueW/2)-4, creditValueY - (creditValueH/2) + 53);
  tft.println(String("$" + String(creditValue)));

  Screen::renderProduct(0);
  Screen::renderProduct(1);
  Screen::renderProduct(2);
  Screen::renderProduct(3);
}

void Screen::system() {
  tft.fillRect(0, 0, 480, 320, GREEN);

  tft.drawFastHLine(0, 70, SCREEN_HEIGHT*2, WHITE);

  String titleLabel = "System Mode";
  int titleLabelX;
  int titleLabelY;
  int titleLabelW;
  int titleLabelH;

  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setFont(&FreeSans9pt7b);

  tft.getTextBounds(titleLabel, SCREEN_WIDTH, (SCREEN_HEIGHT/2), &titleLabelX, &titleLabelY, &titleLabelW, &titleLabelH);
  tft.setCursor(titleLabelX - (titleLabelW/2), 60);
  tft.println(titleLabel);

  String descLabel = "To stock product, press the\ncorresponding button.\n\nTo unlock VendCube's lid, press the \nhidden step button.\n\nTo turn off System Mode, unclick the \nhidden mode button.";
  int descLabelX;
  int descLabelY;
  int descLabelW;
  int descLabelH;

  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  tft.setFont(&FreeSansBold12pt7b);

  tft.setCursor(0, 110);
  tft.println(descLabel);

}

void Screen::product(int productNumber, float credit) {

  String productTitle1;
  String productTitle2;
  String productDesc;
  float productPrice;
  unsigned int productColor;

  switch(productNumber) {
    case 1:
      productTitle1 = PRODUCT_1_TITLE_1;
      productTitle2 = PRODUCT_1_TITLE_2;
      productPrice = PRODUCT_1_PRICE;
      productColor = PRODUCT_1_COLOR;
      productDesc = PRODUCT_1_DESC;
      break;
    case 2:
      productTitle1 = PRODUCT_2_TITLE_1;
      productTitle2 = PRODUCT_2_TITLE_2;
      productPrice = PRODUCT_2_PRICE;
      productColor = PRODUCT_2_COLOR;
      productDesc = PRODUCT_2_DESC;
      break;
    case 3:
      productTitle1 = PRODUCT_3_TITLE_1;
      productTitle2 = PRODUCT_3_TITLE_2;
      productPrice = PRODUCT_3_PRICE;
      productColor = PRODUCT_3_COLOR;
      productDesc = PRODUCT_3_DESC;
      break;
    case 4:
      productTitle1 = PRODUCT_4_TITLE_1;
      productTitle2 = PRODUCT_4_TITLE_2;
      productPrice = PRODUCT_4_PRICE;
      productColor = PRODUCT_4_COLOR;
      productDesc = PRODUCT_4_DESC;
      break;
  }

  tft.fillRect(0, 0, 480, 320, productColor);

  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setFont(&FreeSansBold12pt7b);

  tft.setCursor(10, 60);
  tft.println(productTitle1);

  tft.setCursor(10, 105);
  tft.println(productTitle2);

  tft.setFont(&FreeSans12pt7b);
  tft.setTextSize(1);
  tft.setCursor(10, 145);
  tft.println(productDesc);

  tft.setFont(&FreeSansBold12pt7b);
  tft.setTextSize(1);
  tft.fillRoundRect(14, 270, 100, 60, 10, WHITE);
  tft.setCursor(30, 300);
  tft.setTextColor(BLACK);
  tft.println("BACK");

  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(30, 220);
  tft.setFont(&FreeSans9pt7b);
  tft.println("$" + String(productPrice));

  tft.setFont(&FreeSansBold12pt7b);
  tft.setTextSize(1);
  tft.setCursor(290, 210);
  tft.println("CREDIT");

  tft.setFont(&FreeSans9pt7b);
  tft.setTextSize(3);
  tft.setCursor(290, 260);
  // tft.println("$0.00");

  updateCredit(SCREEN_PRODUCT, productColor, credit);

}

void Screen::updateCredit(int currentScreen, unsigned int color, float credit) {

  if(credit == _lastCredit and currentScreen == _lastScreen) return;

  if(currentScreen == SCREEN_PRODUCT) {

    tft.fillRoundRect(280, 210, 180, 80, 10, color);
    tft.setTextColor(WHITE);
    tft.setFont(&FreeSans9pt7b);
    tft.setTextSize(3);
    tft.setCursor(290, 260);
    tft.println("$" + String(credit));

  }

  if(currentScreen == SCREEN_PRODUCTS) {

    int creditValueX;
    int creditValueY;
    int creditValueW;
    int creditValueH;

    tft.setTextColor(WHITE);
    tft.setFont(&FreeSans9pt7b);
    tft.setTextSize(2);
    tft.getTextBounds(String("$" + String(credit)), SCREEN_WIDTH, (SCREEN_HEIGHT/2), &creditValueX, &creditValueY, &creditValueW, &creditValueH);
    tft.fillRoundRect(172, 140, 136, 40, 10, BLACK);
    tft.setCursor(creditValueX - (creditValueW/2)-4, creditValueY - (creditValueH/2) + 53);
    tft.println(String("$" + String(credit)));

  }

  _lastScreen = currentScreen;
  _lastCredit = credit;

}

void Screen::vend(String productTitle1, String productTitle2) {

  tft.fillRect(0, 0, 480, 320, RED);

  tft.setCursor(0, 80);

  tft.setFont(&FreeSans12pt7b);
  tft.setTextSize(2);

  tft.println("             Vending");

  tft.setTextSize(2);

  tft.setCursor(45, 160);
  tft.println(productTitle1);

  tft.setCursor(45, 210);
  tft.println(productTitle2);

  delay(1000);

  tft.fillRect(0, 0, 480, 320, GREEN);

  tft.setTextSize(2);

  tft.setCursor(125, 160);
  tft.println("Thank you!");

}

void Screen::renderProduct(int productNumber) {

  int16_t  x1, y1;
  uint16_t w, h;

  String productTitle1 = "";
  String productTitle2 = "";
  float productPrice = 0.00;
  unsigned int productColor = BLACK;

  int leftX;
  int topY;
  int quadrantWidth = 320 / 4;
  int quadrantHeight = 240 / 4;

  switch(productNumber) {
    case 0:
      productTitle1 = PRODUCT_1_TITLE_1;
      productTitle2 = PRODUCT_1_TITLE_2;
      productPrice = PRODUCT_1_PRICE;
      productColor = PRODUCT_1_COLOR;
      leftX = quadrantWidth - (quadrantWidth);
      topY = quadrantHeight - (quadrantHeight * 0.70) + 30;
      break;
    case 1:
      productTitle1 = PRODUCT_2_TITLE_1;
      productTitle2 = PRODUCT_2_TITLE_2;
      productPrice = PRODUCT_2_PRICE;
      productColor = PRODUCT_2_COLOR;
      leftX = 3 * quadrantWidth;
      topY = quadrantHeight - (quadrantHeight * 0.70) + 30;
      break;
    case 2:
      productTitle1 = PRODUCT_3_TITLE_1;
      productTitle2 = PRODUCT_3_TITLE_2;
      productPrice = PRODUCT_3_PRICE;
      productColor = PRODUCT_3_COLOR;
      leftX = quadrantWidth - (quadrantWidth);
      topY = 3 * quadrantHeight + 40;
      break;
    case 3:
      productTitle1 = PRODUCT_4_TITLE_1;
      productTitle2 = PRODUCT_4_TITLE_2;
      productPrice = PRODUCT_4_PRICE;
      productColor = PRODUCT_4_COLOR;
      leftX = 3 * quadrantWidth;
      topY = 3 * quadrantHeight + 40;
      break;
  }

  int line1X;
  int line1Y;
  int line1W;
  int line1H;

  int line2X;
  int line2Y;
  int line2W;
  int line2H;

  tft.setFont(&FreeSansBold12pt7b);
  tft.setTextColor(productColor);
  tft.setTextSize(1);

  tft.getTextBounds(productTitle1, leftX, topY, &line1X, &line1Y, &line1W, &line1H);
  tft.setCursor(leftX, topY);
  tft.println(productTitle1);

  tft.setCursor(leftX, topY + 30);
  tft.println(productTitle2);

  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setFont(&FreeSansBold9pt7b);

  tft.setCursor(leftX, topY + 74);
  tft.println("       $" + String(productPrice));
}

void Screen::setup() {
  Serial.begin(9600);

  tft.reset();

  uint16_t identifier = tft.readID();
  Serial.println(String(identifier));
  tft.begin(identifier);
  tft.setRotation(1);
  tft.invertDisplay(true);

}