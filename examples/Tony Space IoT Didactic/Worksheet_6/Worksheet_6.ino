#include <TonyS_X1.h>
#include <TonyS_X1_ExternalModule.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Your ssid";
const char* password = "Your password";
const char* mqttServer = "broker.vsmqtt.space";
const int mqttPort = 1883;

WiFiClient client;
PubSubClient mqtt(client);

unsigned long lastMeasure = 0;
unsigned long interval = 1000;
unsigned long now = 0;

TonySHT31 sht31;

void setup()
{
  Serial.begin(115200);
  Tony.begin();
  sht31.begin(0x44);
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
  now = millis();
  if (now - lastMeasure > interval) {
    lastMeasure = now;
    float t = sht31.readTemperature();
    float h = sht31.readHumidity();
    if (!isnan(h) && !isnan(t)) {
      Serial.println("Temperature : " + String(t));
      Serial.println("Humidity : " + String(h));
      String toPublish = String(t) + " , " + String(h);
      mqtt.publish("temp&humi", toPublish.c_str());
    }
    else {
      Serial.println("Failed to read data from SHT31");
      return;
    }
  }
}
