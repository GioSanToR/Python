import pyfirmata
import time

board = pyfirmata.Arduino('COM3')
led = 9

while True:
    for i in range (100, 2000, 100):
        board.digital[led].write(1)
        time.sleep(i/1000)
        board.digital[led].write(0)
        time.sleep(i/1000)