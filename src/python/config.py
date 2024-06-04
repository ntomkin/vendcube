class Config:
    def __init__(self):
        print("Config initialized")
        # load a env file from /boot/vending.txt
        # read the values and set them as attributes of the class
        with open('/boot/vending.txt', 'r') as file:
            for line in file:
                line = line.strip()
                if line:
                    try:
                        key, value = line.split('=')
                        setattr(self, key, value)
                    except ValueError:
                        print(f"Error parsing line: {line}")
        print(f"Config loaded")