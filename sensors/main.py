import adafruit_dht
import board
import socket
import time

dht = adafruit_dht.DHT11(board.D27)

with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as s:
    s.connect("/tmp/smartwatch.sock")

    while True:
        time.sleep(1)
        s.sendall(bytearray([dht.temperature]))
