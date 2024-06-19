#include <TonyS_X1.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Your ssid";
const char* password = "Your password";

const char* mqttServer = "broker.vsmqtt.space";
const int mqttPort = 1883;

WiFiClient client;
PubSubClient mqtt(client);

bool state = 0;

void setup()
{
  Serial.begin(115200);
  Tony.begin();
  Tony.pinMode(IO10, INPUT_PULLUP);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  mqtt.setServer(mqttServer, mqttPort);
  mqtt.connect("Tony Space");
  Serial.print("Connecting to MQTT...");
  while (!mqtt.connected()) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("MQTT connected");
}

void loop()
{
  mqtt.loop();
  bool value = Tony.digitalRead(IO10);
  if (value != state) {
    state = value;
    Serial.print("value : ");
    Serial.println(value);
    String toPublish = String(value);
    mqtt.publish("dryContact", toPublish.c_str());
  }
}
