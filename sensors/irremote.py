import time

import board
import pulseio

import adafruit_irremote

pulsein = pulseio.PulseIn(board.D27, maxlen=120, idle_state=True)
decoder = adafruit_irremote.NonblockingGenericDecode(pulsein)

t0 = next_heartbeat = time.monotonic()

while True:
    for message in decoder.read():
        # print(f"t={time.monotonic() - t0:.3} New Message")
        # print("Heard", len(message.pulses), "Pulses:", message.pulses)
        if isinstance(message, adafruit_irremote.IRMessage):
          if len(message.code) > 3:
            command = message.code[2]
            print("Command:", command)
        elif isinstance(message, adafruit_irremote.NECRepeatIRMessage):
            print("NEC repeat!")
        elif isinstance(message, adafruit_irremote.UnparseableIRMessage):
            print("Failed to decode", message.reason)
        print("----------------------------")

    # This heartbeat confirms that we are not blocked somewhere above.
    t = time.monotonic()
    if t > next_heartbeat:
        # print(f"t={time.monotonic() - t0:.3} Heartbeat")
        next_heartbeat = t + 0.1
