import pyfirmata
import time

def move_servo(angle):
    servo_pin.write(angle)
    
board=pyfirmata.Arduino('COM3')

iter8 = pyfirmata.util.Iterator(board)
iter8.start()

servo_pin = board.get_pin('d:9:s')
analog_input = board.get_pin('a:0:i')

while True:
    val = analog_input.read()
    if val is not None:
        servo_pin.write(val*175)
    else:
        time.sleep(0.1)
