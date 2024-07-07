// #include <Arduino.h>

// const int ledPin = 1;

void setup()
{
  ESPserial.print("AT+CIOBAUD=9600\r\n");
  ESPserial.begin(9600);
  // pinMode(ledPin, OUTPUT);
  ESPserial.println("READY!");
}

void loop()
{
  ESPserial.println("HIGH");
  // digitalWrite(ledPin, HIGH);
  delay(1000);
  ESPserial.println("LOW");
  // digitalWrite(ledPin, LOW);
  delay(1000);
}
