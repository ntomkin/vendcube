import os
import logging
from waveshare_epd import epd4in2_V2
import time
from PIL import Image,ImageDraw,ImageFont
import traceback
import threading

logging.basicConfig(level=logging.DEBUG)

class Screen:
    def __init__(self):
        self._assetdir = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'assets')

        self._products = []
        self._selected_product = None
        self._credit = 0.0
        self._screen = None
        self._screen_active = None
        self._pending_update = False

        self._font_large = ImageFont.truetype(os.path.join(self._assetdir, 'Omnes-Semibold.ttc'), 35)
        self._font_medium = ImageFont.truetype(os.path.join(self._assetdir, 'Omnes-Semibold.ttc'), 28)
        self._font_small = ImageFont.truetype(os.path.join(self._assetdir, 'Omnes-Regular.ttc'), 25)

        self._image_select_product = Image.open(os.path.join(self._assetdir, 'select-product.bmp'))
        self._image_boot = Image.open(os.path.join(self._assetdir, 'boot.bmp'))

        self._thread = threading.Thread(target=self._screen_check_loop)
        self._thread.daemon = True  
        self._thread.start()

    def clear(self):
        logging.info("Clear")
        self._epd.Clear()

    def sleep(self):
        logging.info("Sleep")
        self._epd.sleep()

    def boot(self):
        logging.info("Boot")

        draw = ImageDraw.Draw(self._image_boot)

        self._epd.display(self._epd.getbuffer(self._image_boot))

    def choice(self):
        logging.info("Choice")
        self._epd.init()

        draw = ImageDraw.Draw(self._image_select_product)
        areas = [(10, 10), (300, 10), (10, 160), (300, 160), (10, 400)]

        for i, product in enumerate(self._products):
            area_name = areas[i]
            area_price = (area_name[0], area_name[1] + 20)
            draw.text(area_name, product["name"], font = self._font_small, fill = 0)
            draw.text(area_price, f'${float(product["price"]):.2f}', font = self._font_medium, fill = 0)

        if self._selected_product is not None:
            draw.text((150, 100), self._selected_product['name'], font = self._font_large, fill = self._epd.GRAY3)
            selected_product_price = self._selected_product['price']
        
        draw.text((155, 175), f'${self._credit:.2f}', font = self._font_large, fill = self._epd.GRAY3)

        if self._selected_product is not None:
            draw.text((155, 245), f'${float(selected_product_price):.2f}', font = self._font_large, fill = self._epd.GRAY3)

        self._epd.display(self._epd.getbuffer(self._image_select_product))

        self._epd.reset()

        time.sleep(2)

    def _screen_check_loop(self):
        self._epd = epd4in2_V2.EPD()
        self._epd.init()

        while True:
            try:
                if self._products and self._screen == "choice" and (self._screen_active != "choice" or self._pending_update):
                    self._screen_active = "choice"
                    self.choice()

                if self._screen == "boot" and self._screen_active != "boot":
                    self._screen_active = "boot"
                    self.boot()
            
                self._pending_update = False

                time.sleep(.1)

            except KeyboardInterrupt:
                self._epd.sleep()
                epd4in2_V2.epdconfig.module_exit(cleanup=True)
                break

            except Exception as e:
                logging.info(f"Error in screen check loop: {e}")
                self._epd.sleep()
                epd4in2_V2.epdconfig.module_exit(cleanup=True)
                break

    def set_products(self, products):
        self._products = products

    def set_screen(self, screen):
        self._screen = screen

    def update(self, selected_product, credit):
        if selected_product != self._selected_product or credit != self._credit:
            self._selected_product = selected_product
            self._credit = credit
            self._pending_update = True
