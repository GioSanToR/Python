import pyfirmata
import time

board = pyfirmata.Arduino('COM5')
it = pyfirmata.util.Iterator(board)
it.start()

led = board.get_pin('d:9:p')

while True:
    data = float(input('Write a number between 0 and 1: '))
    if 0 < data <= 1:
        led.write(data)
        print(f'LED is ON with {round(data*100)}% brightness')
    elif data == 0:
        led.write(0)
        print('LED is OFF')
    else:
        print('Write only  a number between 0 and 1')