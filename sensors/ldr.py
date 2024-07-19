import board
import digitalio
import time

sensor = digitalio.DigitalInOut(board.D24)
sensor.direction = digitalio.Direction.INPUT

while True:
    time.sleep(1)
    print("T:{:.0f}".format(sensor.value))
