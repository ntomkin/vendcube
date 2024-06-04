import RPi.GPIO as GPIO
from time import time, clock_gettime, sleep
import threading

class Inputs:
    def __init__(self):
        self._buttons = []
        self._callback = None
        # Create a thread for the while loop
        self._thread = threading.Thread(target=self._button_check_loop)
        self._thread.daemon = True  # Set the thread as a daemon so it exits when the main program ends
        self._thread.start()  # Start the thread

        print("Inputs initialized")

    def _button_check_loop(self):
        while True:
            try:
                for button in self._buttons:
                    if GPIO.input(int(button[1])) == GPIO.LOW:
                        # print(f"Button {button[0]} pressed on PIN {button[1]}")
                        # print("================")
                        self._callback(button[0])
                sleep(.1)
            except KeyboardInterrupt:
                GPIO.cleanup()
                break
            except Exception as e:
                print(f"Error in button check loop: {e}")
                GPIO.cleanup()
                break

    def set_callback(self, callback):
        print("Inputs callback set") 
        self._callback = callback

    def add_button(self, button, pin):
        print(f"Button added: {button} at {pin}")
        if pin:
            try:
                GPIO.setmode(GPIO.BCM)
                GPIO.setup(int(pin), GPIO.IN, pull_up_down=GPIO.PUD_UP)
                self._buttons.append([button, pin])
            except Exception as e:
                print("Error setting up button input", e)