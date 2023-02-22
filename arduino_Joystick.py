import pyfirmata
import time
from math import floor

board = pyfirmata.Arduino('COM3')
it = pyfirmata.util.Iterator(board)
it.start()

analog_input1 = board.get_pin('a:0:i')
analog_input2 = board.get_pin('a:1:i')

joy_button = board.get_pin('d:3:i')#use a pull-up resitor (10k Ohms) in the circuit

led1 = board.get_pin('d:7:o')
led2 = board.get_pin('d:8:o')
led3 = board.get_pin('d:9:o')
led4 = board.get_pin('d:10:o')
led5 = board.get_pin('d:11:o')

while True:
    xValue = analog_input1.read()
    yValue = analog_input2.read()
    button_state = joy_button.read()
    if xValue and yValue is not None:
        if button_state:
            led5.write(0)
        else:
            led5.write(1)
        if xValue>=0 and yValue<=0.2:
            led1.write(1)
        else:
            led1.write(0)
        if xValue<=0.1 and yValue>=0.4:
            led2.write(1)
        else:
            led2.write(0)
        if xValue>=0.9 and yValue>=0.4:
            led3.write(1)
        else:
            led3.write(0)
        if xValue>=0.4 and yValue>=0.9:
            led4.write(1)
        else:
            led4.write(0)
    else:
        time.sleep(0.1)
    print(xValue,yValue, button_state)
    