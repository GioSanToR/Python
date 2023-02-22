import pyfirmata
import time

board = pyfirmata.Arduino('COM3')

it = pyfirmata.util.Iterator(board)
it.start()

lastButton = False
currentButton = False
ledMode = 0

button = board.get_pin('d:2:i')
Bled = board.get_pin('d:9:o')
Gled = board.get_pin('d:10:o')
Rled = board.get_pin('d:11:o')

def debounce(last):
    current = button.read()
    if last != current:
        time.sleep(0.005)
        current = button.read()
    return current

def setMode(mode):
    if mode == 1: #RED 
        Rled.write(0)
        Gled.write(1)
        Bled.write(1)
    elif mode == 2: #GREEN 
        Rled.write(1)
        Gled.write(0)
        Bled.write(1) 
    elif mode== 3:  #BLUE 
        Rled.write(1)
        Gled.write(1)
        Bled.write(0)
    elif mode == 4: #RED + BLUE
        Rled.write(0)
        Gled.write(1)
        Bled.write(0)
    elif mode == 5: #BLUE + GREEN
        Rled.write(0)
        Gled.write(0)
        Bled.write(1)
    elif mode == 6: #GREEN + RED
        Rled.write(1)
        Gled.write(0)
        Bled.write(0)
    elif mode == 7: #GREEN + RED + BLUE
        Rled.write(0)
        Gled.write(0)
        Bled.write(0)
    else:
        Rled.write(1)
        Gled.write(1)
        Bled.write(1)

while True:
    if ledMode < 8:
        currentButton = debounce(lastButton)
        if lastButton is False and currentButton is True:
            ledMode += 1
        lastButton = currentButton
        setMode(ledMode)
    else:
        ledMode = 0
    