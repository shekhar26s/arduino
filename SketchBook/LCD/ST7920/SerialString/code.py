#!/usr/bin/python

import serial
ser = serial.Serial('/dev/ttyACM0', 9600)

ser.write('baca')

while True:
  sArduino = ser.readline()
  print sArduino.rstrip()
