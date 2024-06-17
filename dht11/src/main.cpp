#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <PubSubClient.h>

const char *wifi_ssid = "BL05_AP404_2G";  // SSID
const char *wifi_password = "W1fi$2021";  // WIFI
const unsigned int writeInterval = 25000; // write interval (in ms)

const char* mqtt_server = "192.168.1.110";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	256
char msg[MSG_BUFFER_SIZE];

const char *iot_server_host = "iotserver";
const int iot_server_port = 443;

#define DHTPIN 2 // Pin which is connected to the DHT sensor.
// Uncomment the type of sensor in use:
#define DHTTYPE DHT11 // DHT 11
// #define DHTTYPE           DHT22     // DHT 22 (AM2302)
// #define DHTTYPE           DHT21     // DHT 21 (AM2301)
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
int status = WL_IDLE_STATUS;
float myTemperature = 0, myHumidity = 0;

// WiFiClient client;


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("home/sensors", "hello world");
      // ... and resubscribe
      // client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup_wifi() {
  WiFi.begin(wifi_ssid, wifi_password);
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  // for (int i = 0; i < length; i++) {
  //   Serial.print((char)payload[i]);
  // }
  // Serial.println();

  // // Switch on the LED if an 1 was received as first character
  // if ((char)payload[0] == '1') {
  //   digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
  //   // but actually the LED is on; this is because
  //   // it is active low on the ESP-01)
  // } else {
  //   digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  // }

}

void setup()
{
  Serial.begin(9600);
  Serial.println();
  // Serial.println(WiFi.localIP());
  // Initialize device.

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);


  dht.begin();
  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print("Sensor:       ");
  Serial.println(sensor.name);
  Serial.print("Driver Ver:   ");
  Serial.println(sensor.version);
  Serial.print("Unique ID:    ");
  Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    ");
  Serial.print(sensor.max_value);
  Serial.println(" *C");
  Serial.print("Min Value:    ");
  Serial.print(sensor.min_value);
  Serial.println(" *C");
  Serial.print("Resolution:   ");
  Serial.print(sensor.resolution);
  Serial.println(" *C");
  Serial.println("------------------------------------");

  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print("Sensor:       ");
  Serial.println(sensor.name);
  Serial.print("Driver Ver:   ");
  Serial.println(sensor.version);
  Serial.print("Unique ID:    ");
  Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    ");
  Serial.print(sensor.max_value);
  Serial.println("%");
  Serial.print("Min Value:    ");
  Serial.print(sensor.min_value);
  Serial.println("%");
  Serial.print("Resolution:   ");
  Serial.print(sensor.resolution);
  Serial.println("%");
  Serial.println("------------------------------------");
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  // Set Client to insecure
  // client.setInsecure();
}

void loop()
{
  // Read data from DHT
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature))
  {
    Serial.println("Error reading temperature!");
  }
  else
  {
    // Update temperature and humidity
    myTemperature = (float)event.temperature;
    Serial.print("Temperature: ");
    Serial.print(myTemperature);
    Serial.println(" C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity))
  {
    Serial.println("Error reading humidity!");
  }
  else
  {
    myHumidity = (float)event.relative_humidity;
    Serial.print("Humidity: ");
    Serial.print(myHumidity);
    Serial.println("%");
  }

  // Use WiFiClientSecure class to create TLS connection
  // Serial.print("********** connecting to HOST : ");
  // Serial.println(iot_server_host);
  // if (!client.connect(iot_server_host, iot_server_port))
  // {
  //   Serial.println("-> connection failed");
  //   // return;
  // }
  /* ignore certificate verification
  if (client.verify(https_fingerprint, iot_server_host)) {
    Serial.println("-> certificate matches");
  } else {
    Serial.println("-> certificate doesn't match");
  }
  */
  // Create a URL for the request
  // String url = "/write/";
  // url += apiKeyIn;
  // url += "?module1=";
  // url += myTemperature;
  // url += "&module2=";
  // url += myHumidity;

  // Serial.print("********** requesting URL: ");
  // Serial.println(url);

  // client.print(String("GET ") + url + " HTTP/1.1\r\n" +
  //              "Host: " + iot_server_host + "\r\n" +
  //              "Connection: close\r\n\r\n");

  // Serial.println("> Request sent to ASKSENSORS");
  // while (client.connected())
  // {
  //   String line = client.readStringUntil('\n');
  //   if (line == "\r")
  //   {
  //     String line = client.readStringUntil('\n');
  //     Serial.println("********** ASKSENSORS replay:");
  //     Serial.println(line);
  //     Serial.println("********** closing connection");

  //     break;
  //   }
  // }

  if (!client.connected())
  {
    reconnect();
  }

  client.loop();

  unsigned long now = millis();

  if (now - lastMsg > 2000)
  {
    lastMsg = now;
    snprintf(msg, MSG_BUFFER_SIZE, "{\"t\":20,\"h\":0,\"p\":0,\"l\":0,\"b\":0,\"s\":0,\"r\":0,\"g\":0,\"d\":0,\"m\":0,\"c\":0,\"f\":0,\"e\":0,\"a\":0,\"i\":0,\"o\":0,\"n\":0,\"u\":0,\"v\":0,\"w\":0,\"y\":0,\"z\":0,\"x\":0,\"q\":0,\"j\":0,\"k\":0}");
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("home/sensors", msg);
  }

  delay(writeInterval); // delay in msec
}
