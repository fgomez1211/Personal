import serial

# define the serial connection. replace 'port' with the actual port
ser = serial.Serial('/dev/cu.usbmodem101', 115200)

def send_data(data):
    ser.write(data.encode()) # convert string to bytes and send over serial
    print('Sent data: ', data)

data = '10'
send_data(data)
