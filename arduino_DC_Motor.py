import pyfirmata
import time
import tkinter
from tkinter import *
#using L298N Motor Driver

board = pyfirmata.Arduino('COM3')
it = pyfirmata.util.Iterator(board)
it.start()

motor1pin1 = board.get_pin('d:9:p')
motor1pin2 = board.get_pin('d:10:p')

def motor_right():
    for i in range (0, 1000, 1):
        motor1pin1.write(i/1000)
        time.sleep(0.01)
    time.sleep(2)
    for i in range (1000, 0, -1):
        motor1pin1.write(i/1000)
        time.sleep(0.01)
    time.sleep(2)

def motor_left():
    for i in range (0, 1000, 1):
        motor1pin2.write(i/1000)
        time.sleep(0.01)
    time.sleep(2)
    for i in range (1000, 0, -1):
        motor1pin2.write(i/1000)
        time.sleep(0.01)
    time.sleep(2)

def motor_off():
    motor1pin1.write(0)
    motor1pin2.write(0)

root = Tk()
root.title("Control de colores RGB")
root.geometry("465x225")
root.configure(bg="#FFFFFF")
color_boton = "#9C7FB5"
color_letra = "#2E2536"

btn_right = Button(root, text="Turn Right", bg=color_boton, fg=color_letra,
command=lambda: motor_right())
btn_right.grid(column=1, row=1, ipadx=24, pady=3, padx=3)

btn_left = Button(root, text="Turn Left", bg=color_boton, fg=color_letra,
command=lambda: motor_left())
btn_left.grid(column=1, row=2, ipadx=24, pady=3, padx=3)

btn_off = Button(root, text="Turn off", bg=color_boton, fg=color_letra,
command=lambda: motor_off())
btn_off.grid(column=1, row=2, ipadx=24, pady=3, padx=3)

root.mainloop()

