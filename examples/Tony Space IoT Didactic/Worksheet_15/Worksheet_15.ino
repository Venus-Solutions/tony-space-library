#include <TonyS_X1.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define LED LED_BUILTIN

unsigned long lastMeasure = 0;
unsigned long interval = 3000;
unsigned long now = 0;
const char* ssid = "Your SSID";
const char* password = "Your Password";
const char* mqttServer = "Your Raspberry Pi’s IP Address";
const int mqttPort = 1883;

WiFiClient tonySpaceClient;
PubSubClient mqtt(tonySpaceClient);

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  Serial.println();
  String message = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    message += (char)payload[i];
  }
  if (String(topic) == "LED") {
    if (message == "LED ON") {
      Tony.digitalWrite(LED, HIGH);
      Serial.println(" ==> LED IS ON");
    }
    else {
      Tony.digitalWrite(LED, LOW);
      Serial.println(" ==> LED IS OFF");
    }
  }
  Serial.println("");
}

void setup() {
  Serial.begin(115200);
  Tony.begin();
  Tony.pinMode(LED, OUTPUT);
  Tony.digitalWrite(LED, LOW);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - IP address: ");
  Serial.println(WiFi.localIP());
  mqtt.setServer(mqttServer, mqttPort);
  mqtt.setCallback(callback);
  while (!mqtt.connected()) {
    Serial.println("Connecting to MQTT...");
    if (mqtt.connect("Tony Space Client")) {
      mqtt.subscribe("LED");
      Serial.println("connected");
    }
    else {
      Serial.print("failed with state ");
      Serial.print(mqtt.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}

void loop() {
  mqtt.loop();
  now = millis();
  if (now - lastMeasure > interval) {
    lastMeasure = now;
    String message = "Message from Tony Space";
    mqtt.publish("message", message.c_str());
  }
}
