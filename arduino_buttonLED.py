import pyfirmata
import time

board = pyfirmata.Arduino('COM3')

it = pyfirmata.util.Iterator(board)
it.start()

button = board.get_pin('d:2:i')
led = board.get_pin('d:9:o')

while True:
    if button.read() is True:
        led.write(1)
    else:
        led.write(0)
    time.sleep(0.1)


