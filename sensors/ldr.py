import board
import digitalio
import time

# sensor = digitalio.DigitalInOut(board.D25)
# sensor.direction = digitalio.Direction.INPUT

switch = digitalio.DigitalInOut(board.D26)
switch.direction = digitalio.Direction.OUTPUT

while True:
    time.sleep(1)
    switch.value = not switch.value
    # print("T:{:.0f}".format(sensor.value))
