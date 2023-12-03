

import serial
arduino_port = "/dev/cu.usbmodem101"
baud = 115200
fileName="analog-data.csv"

samples=50000
print_labels = False

ser = serial.Serial(arduino_port,baud)

ser.write('GOH',bytes)


line = 0

while line <=samples:
    if print_labels:
        if line ==0:
            print("Printing Column Headers")
        else:
            print("Line" + str(line)+": writing..")
    getData=str(ser.readline())
    data=getData[0:][:-2]
    print(data)

