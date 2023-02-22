
import pyfirmata
from tkinter import *

def move_servo(angle):
    servo_pin.write(angle)
    

board=pyfirmata.Arduino('COM3')

iter8 = pyfirmata.util.Iterator(board)
iter8.start()

servo_pin = board.get_pin('d:9:s')

root = Tk()
scale = Scale(root, command = move_servo, to = 175, 
            orient = HORIZONTAL, length = 400, label = 'Angle')
scale.pack(anchor = CENTER)

root.mainloop()

