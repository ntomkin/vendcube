from time import sleep
from config import Config
from screen import Screen
from coin import Coin
from inputs import Inputs
from motors import Motors

class Program:
    def __init__(self):
        self.credit = 3.0
        self.product_selected = None
        self.products = []
        self.system_mode = False
        
        self.config = Config()
        self.coin = Coin()
        self.inputs = Inputs()
        self.motors = Motors()
        self.screen = Screen()

        self.inputs.set_callback(self.on_input)
        self.coin.set_callback(self.on_coin)
        
        for option in self.config.__dict__:
            if option.endswith('_BUTTON'):
                self.inputs.add_button(option, self.config.__dict__[option])

        self.coin.add_coin_acceptor(self.config.COIN_INPUT)

        for option in self.config.__dict__:
            if option.endswith('_MOTOR'):
                self.motors.add_motor(int(self.config.__dict__[option]))

        for option in self.config.__dict__:
            if option.startswith('PRODUCT_') and option.endswith('_TITLE'):
                option_prefix = option.replace('_TITLE', '')
                self.products.append({
                    "id": option_prefix,
                    "name": self.config.__dict__[option_prefix + '_TITLE'],
                    "price": self.config.__dict__[option_prefix + '_PRICE'],
                    "rotation": self.config.__dict__[option_prefix + '_ROTATION'],
                    "button": self.config.__dict__[option_prefix + '_BUTTON'],
                    "motor": self.config.__dict__[option_prefix + '_MOTOR'],
                })

        self.screen.set_screen("boot")
        self.screen.update(self.product_selected, self.credit)

        print(f"Credit: {self.credit}")

        self.motors.slide(4, True)

    def start(self):
        print("Program started")
        while True:
            try:
                # if problems with system_mode, uncomment this
                sleep(1)
                self.system_mode = False

                self.screen.set_products(self.products)
                self.screen.set_screen("choice")
            except KeyboardInterrupt:
                break

    def on_input(self, value):
        if value.startswith('SYSTEM_MODE_'):
            self.system_mode = True

        if value.startswith('PRODUCT_') and self.system_mode == False:
            self.product_selected = next((product for product in self.products if product["id"] == value.replace('_BUTTON', '')), None)
            print(f"Product selected: {self.product_selected['id']}")
            self.check_if_credit_sufficient()

        if value.startswith('PRODUCT_') and self.system_mode == True:
            # goes in reverse to allow loading the product
            self.motors.stock_product(value[:-7], int(self.config.__dict__[value[:-7] + '_MOTOR']), int(self.config.__dict__[value[:-7] + '_ROTATION']))

        if value.startswith('SYSTEM_STEP_') and self.system_mode == False:
            self.credit += float(.25)
            print(f"Credit: {self.credit}")
            
        self.screen.update(self.product_selected, self.credit)

    def on_coin(self, value):
        print(f"Coin: {value}")
        self.credit += value
        print(f"Credit: {self.credit}")
        self.check_if_credit_sufficient()

        self.screen.update(self.product_selected, self.credit)

    def check_if_credit_sufficient(self):
        if self.product_selected and self.credit >= float(self.product_selected['price']):
            self.motors.vend_product(self.product_selected, int(self.product_selected['motor']), int(self.product_selected['rotation']))
            self.credit -= float(self.product_selected['price'])
            self.product_selected = None
            print(f"Credit: {self.credit}")

        self.screen.update(self.product_selected, self.credit)

program = Program()
program.start()
