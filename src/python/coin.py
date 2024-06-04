import RPi.GPIO as GPIO
from time import time, clock_gettime, sleep
import threading

class Coin:
    def __init__(self):
        self.callback = None
        self.coin_acceptor = None
        self.pulses_last_time = time()
        self.pulses_last_total = 0
        self.pulse_value = .25

        self._thread = threading.Thread(target=self._coin_check_loop)
        self._thread.daemon = True  
        self._thread.start()  
        
        print("Coin receptacle initialized")

    def add_coin_acceptor(self, pin):
        self.coin_acceptor = int(pin)
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(int(self.coin_acceptor), GPIO.IN, pull_up_down=GPIO.PUD_UP)
        GPIO.add_event_detect(int(self.coin_acceptor), GPIO.RISING, callback=self.counter, bouncetime=1)

        print("Coin added: COIN_INPUT at", pin)

    def set_callback(self, callback):
        if callback:
            self.callback = callback

    def _coin_check_loop(self):
        while True:
            try:
                pass

            except KeyboardInterrupt:
                GPIO.cleanup()

    def counter(self, channel):
        if GPIO.input(self.coin_acceptor):
            self.pulses_last_total += 1
            self.pulses_last_time = time()

        if self.callback:
            self.callback(self.pulses_last_total * self.pulse_value)
            self.pulses_last_total = 0