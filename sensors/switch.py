import board
import digitalio
import time

switch = digitalio.DigitalInOut(board.D26)
switch.direction = digitalio.Direction.OUTPUT

while True:
    time.sleep(1)
    switch.value = not switch.value
