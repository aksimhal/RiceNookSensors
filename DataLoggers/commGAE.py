#comm and gae
#01-14-13
#Requires PySerial Library 

import urllib
import serial

ser = serial.Serial()  # create serial port object
ser.baudrate = 57600
ser.port = 21 #if it is com port 3, note com port as 2

ser.open() #open serial port 

print ser.portstr       # check which port was really used

while ser.isOpen():
	response = ser.read(10)
	#print "trying to read" 
	print response
	u = urllib.urlopen('http://localhost:8888/guestbook',data=urllib.urlencode({'id': response}))
	
print "done" 