import pyfirmata
import time

board = pyfirmata.Arduino('COM4')

led = board.get_pin('d:9:p')
'''a analog pin, Pin number, i for input, d digital pin, Pin number,  o for output, p for pwm (Pulse-width modulation)'''

while True:
    for i in range(0, 1000, 10):
        led.write(i/1000)
        time.sleep(0.1)
    for i in range(1000, 0, -10):
        led.write(i/1000)
        time.sleep(0.1)