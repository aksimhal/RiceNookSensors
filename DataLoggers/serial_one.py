#pyserial test
#08-14-12
#Requires PySerial Library 

import serial

ser = serial.Serial()  # create serial port object
ser.baudrate = 57600
ser.port = 2 #if it is com port 3, note com port as 2

ser.open() #open serial port 

print ser.portstr       # check which port was really used

while ser.isOpen():
	response = ser.read(10)
	print "trying to read" 
	print response
print "done" 