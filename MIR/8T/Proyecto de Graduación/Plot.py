import matplotlib.pyplot as plt
import numpy as np
import serial

# Establish Serial Connection
ser = serial.Serial('/dev/cu.usbmodem101', 115200)

# Data Lists
data = []
time = []

# Loop
while True:
    # Read Data from Serial
    arduinoData = ser.readline()

    # If the Serial Buffer is Empty
    if not arduinoData:
        break

    # Convert the Read Data to Float
    value = float(arduinoData.decode().strip())

    # Append the Data and Time
    data.append(value)
    time.append(len(data))

    # Sleep for 0.1 seconds
    plt.pause(0.1)

# Close the Serial Connection
ser.close()

# Plot the Data
plt.figure(figsize=(10, 7))
plt.plot(time, data, 'b', label='Arduino Data')
plt.title('Arduino Serial Data Plot')
plt.xlabel('Time')
plt.ylabel('Value')
plt.legend(loc='upper right')
plt.show()