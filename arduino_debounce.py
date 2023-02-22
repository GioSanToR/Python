import pyfirmata
import time

board = pyfirmata.Arduino('COM3')

it = pyfirmata.util.Iterator(board)
it.start()

lastButton = False
currentButton = False
ledOn = False

button = board.get_pin('d:2:i')
led = board.get_pin('d:9:o')

def debounce(last):
    current = button.read()
    if last != current:
        time.sleep(0.005)
        current = button.read()
    return current

while True:
    currentButton = debounce(lastButton)
    if lastButton is False and currentButton is True:
        ledOn = not ledOn
    lastButton = currentButton
    led.write(ledOn)