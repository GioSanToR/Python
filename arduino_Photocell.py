import pyfirmata
import time

board = pyfirmata.Arduino('COM3')
it = pyfirmata.util.Iterator(board)
it.start()

analog_input = board.get_pin('a:0:i')
led = board.get_pin('d:9:p')

while True:
    analog_value = analog_input.read()
    if analog_value is not None:
        led.write(1-analog_value)
        print(analog_value)
    else:
        time.sleep(0.1)
    time.sleep(0.1)