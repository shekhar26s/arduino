#!/usr/bin/python

import serial
import time
arduino = serial.Serial('/dev/ttyACM0', 115200, bytesize=8, parity='N', stopbits=1, timeout=1)

arduino.isOpen()
time.sleep(5)

arduino.write("hola red")

response = arduino.readline().rstrip()
print response

arduino.close()
