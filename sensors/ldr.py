import board
import digitalio
import time

sensor = digitalio.DigitalInOut(board.D25)
sensor.direction = digitalio.Direction.INPUT

while True:
    time.sleep(1)
    print(sensor.value)
