import serial

# define the serial connection. replace 'port' with the actual port
port = '/dev/cu.usbmodem101'
baud_rate = 115200

ser = serial.Serial(port,baud_rate)
data = 10
ser.write(data)
