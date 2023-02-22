import pyfirmata
import time

board = pyfirmata.Arduino('COM3')
it = pyfirmata.util.Iterator(board)
it.start()

analog_input1 = board.get_pin('a:0:i')
analog_input2 = board.get_pin('a:1:i')
led = board.get_pin('d:9:o')

while True:
    analog_value1 = analog_input1.read()
    analog_value2 = analog_input2.read()
    if analog_value1 and analog_value2 is not None:
        print(f'Analog 0 {analog_value1}, Analog 1 {analog_value1}')
        time.sleep(0.5)
    else:
        time.sleep(0.1)