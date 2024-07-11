import adafruit_dht
import board
import socket
import time

dht = adafruit_dht.DHT11(board.D23)

with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as s:
    s.connect("/tmp/smartwatch.sock")

    while True:
        time.sleep(1)
        try:
            s.sendall("T:{:.0f}".format(dht.temperature))
            print("Temp: {:.1f} *C \t Humidity: {}%".format(dht.temperature, dht.humidity))
        except RuntimeError as e:
            print("Reading from DHT failure: ", e.args)
