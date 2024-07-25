#define WAIT_BEFORE_RESET_STATE_MILLISECONDS 15000

#define	WHITE   0xFFFF
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x02E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define BLACK   0x0000

#define DISPENSE -1
#define STOCK 1
#define OPEN 1
#define CLOSE -1
#define LOCK -1
#define UNLOCK 1

#define SCREEN_NONE 0
#define SCREEN_PRODUCTS 1
#define SCREEN_PRODUCT 2
#define SCREEN_SYSTEM_MODE 3
#define SCREEN_VENDING 4

#define SLIDE_MOTOR_PIN 37
#define SLIDE_ROTATION 0.9
#define LOCK_MOTOR_PIN 53
#define LOCK_ROTATION 1
#define COIN_PIN A7

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define SYSTEM_MODE_BUTTON_PIN 33
#define SYSTEM_STEP_BUTTON_PIN 31

#define PRODUCT_1_TITLE_1 "        Pokemon"
#define PRODUCT_1_TITLE_2 "       Card Stand"
#define PRODUCT_1_DESC "                     With card protector"
#define PRODUCT_1_BUTTON_PIN 25
#define PRODUCT_1_MOTOR_PIN 41
#define PRODUCT_1_PRICE 2.50
#define PRODUCT_1_ROTATION 1.25
#define PRODUCT_1_COLOR 0x001F

#define PRODUCT_2_TITLE_1 "         Pokemon"
#define PRODUCT_2_TITLE_2 "      Cards 5 Pack"
#define PRODUCT_2_DESC "                       With 1 Rare/Halo"
#define PRODUCT_2_BUTTON_PIN 27
#define PRODUCT_2_MOTOR_PIN 43 
#define PRODUCT_2_PRICE 2.00
#define PRODUCT_2_ROTATION 1.25
#define PRODUCT_2_COLOR 0x02E0

#define PRODUCT_3_TITLE_1 "         Pokemon"
#define PRODUCT_3_TITLE_2 "    Stickers 5 Pack"
#define PRODUCT_3_DESC "                     Assorted characters"
#define PRODUCT_3_BUTTON_PIN 23
#define PRODUCT_3_MOTOR_PIN 45
#define PRODUCT_3_PRICE 2.00
#define PRODUCT_3_ROTATION 1.25
#define PRODUCT_3_COLOR 0xF800

#define PRODUCT_4_TITLE_1 "        Pokemon"
#define PRODUCT_4_TITLE_2 "   Stickers 10 Pack"
#define PRODUCT_4_DESC "                     Assorted characters"
#define PRODUCT_4_BUTTON_PIN 29
#define PRODUCT_4_MOTOR_PIN 47
#define PRODUCT_4_PRICE 3.50
#define PRODUCT_4_ROTATION 1.25
#define PRODUCT_4_COLOR 0x1FE0
