from board import SCL, SDA
from time import time, clock_gettime, sleep
import busio
import RPi.GPIO as GPIO
from adafruit_pca9685 import PCA9685
from adafruit_motor import servo
i2c = busio.I2C(SCL, SDA)
pca = PCA9685(i2c, address = 0x40)

class Motors:
    def __init__(self):
        self.motors = []
        self.slide_out = False
        pca.frequency = 40
        print("Motors initialized")

    def add_motor(self, motor):
        try:
            pca.channels[motor].duty_cycle = 0x7FFF
            pca.frequency = 40
            servo_motor = servo.ContinuousServo(pca.channels[motor])
            self.motors.append(servo_motor)
            print(f"Motor added: {motor}")

        except Exception as e:
            print("Error setting up motor", e)

    def vend_product(self, product, motor, rotation):
        print(f"Vending product: {product['id']}")
        try:
            self.slide(4)

            self.motors[motor].throttle = -1
            sleep(rotation)
            self.motors[motor].throttle = 0
            pca.channels[motor].duty_cycle = 0x7FFF
            
            sleep(0.5)

            self.slide(4)

            print(f"Product vended: {product['id']}")

        except Exception as e:
            print("Error vending product", e)

    def stock_product(self, product, motor, rotation):
        print(f"Stocking product: {product}")
        try:
            self.motors[motor].throttle = 0 

            for i in range(rotation):
                self.motors[motor].throttle = 1
                sleep(rotation)
                self.motors[motor].throttle = 0
                pca.channels[motor].duty_cycle = 0x7FFF


            print(f"Product stocked: {product}")

        except Exception as e:
            print("Error stocking product", e)

    def slide(self, motor, force_close = False):
        try:
            if self.slide_out == False and force_close == False:
                pca.frequency = 40
                print(f"Opening slide for product dispensing")
                self.motors[motor].throttle = 1
                self.slide_out = True
                sleep(0.95)
            else:
                print(f"Closing slide for product dispensing")
                pca.frequency = 100
                self.motors[motor].throttle = 0
                self.slide_out = False
                sleep(0.8)

            pca.channels[motor].duty_cycle = 0x7FFF

        except Exception as e:
            print("Error moving slide", e)