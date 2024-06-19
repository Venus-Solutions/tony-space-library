#include <TonyS_X1.h>
#include <TonyS_X1_ExternalModule.h>

NBIoT nb;
NBIoT_MQTT mqtt;

#define SERVER_IP "broker.vsmqtt.space"
#define SERVER_PORT 1883
#define USER ""
#define PASS ""
#define CLIENT_ID "TonySpace_NBIoT"

bool newData = false;
float flat, flon;
unsigned long chars;
unsigned short sentences, failed;
unsigned long lastMeasure = 0;
unsigned long interval = 3000;
unsigned long now = 0;

void setup()
{
  Serial.begin(115200);
  Tony.begin();
  Serial.println("\nNBIoT Setting");
  nb.begin(SLOT5);
  Serial.println("NBIoT Ready");
  Serial.print("SIM(S/N) :");
  Serial.println(nb.getSIMSerial());
  Serial.print("IMEI :");
  Serial.println(nb.getIMEI());
  Serial.print("IMSI :");
  Serial.println(nb.getIMSI());
  Serial.print("Network Status:");
  while (!nb.getNetworkStatus())
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("OK");
  Serial.print("Signal :");
  Serial.println(nb.getSignal());
  Serial.print("Signal :");
  Serial.print(nb.getSignaldBm());
  Serial.println("dBm");
  Serial.print("Signal Level :");
  Serial.println(nb.getSignalLevel());
  Serial.print("Device IP :");
  Serial.println(nb.getDeviceIP());
  Serial.println("");
  TonyGPS.slot(SLOT1);
  TonyGPS.begin(9600);
  TonyGPS.GPS_ForceOn(1);
  Serial.print("GPS library v.");
  Serial.println(TonyGPS.library_version());
  Serial.println();
  Serial.println("Go to Full mode");
  TonyGPS.println("Wake-up please");
}

void loop()
{
  if (!mqtt.connected())
  {
    Serial.println("Open Server...");
    if (mqtt.open(SERVER_IP, SERVER_PORT))
    {
      Serial.print("Connecting to MQTT...");
      if (mqtt.connect(CLIENT_ID, USER, PASS))
      {
        Serial.println("OK");
      }
      else Serial.println("Can't be connected MQTT");
    }
    else Serial.println("Can't be opened server");
  }
  now = millis();
  if (now - lastMeasure > interval)
  {
    lastMeasure = now;
    Serial.println("");
    while (TonyGPS.available()) {
      char c = TonyGPS.read();
      if (TonyGPS.encode(c)) {
        newData = true;
      }
    }
    if (newData) {
      TonyGPS.f_get_position(&flat, &flon);
      if (flat == TonyGPS.GPS_INVALID_F_ANGLE &&
          flon == TonyGPS.GPS_INVALID_F_ANGLE) {
        Serial.print("LATITUDE = 0.0, LONGITUDE = 0.0");
      }
      else {
        Serial.print("LATITUDE = ");
        Serial.print(flat, 6);
        Serial.print(", ");
        Serial.print("LONGITUDE = ");
        Serial.println(flon, 6);
        String toPublish = String(flat, 6) + " , " +
                           String(flon, 6);
        Serial.print(toPublish + " is publishing...");
        if (mqtt.publish("location", toPublish.c_str())) {
          Serial.println("OK");
        }
        else {
          Serial.println("Can't be published topic");
        }
      }
      TonyGPS.stats(&chars, &sentences, &failed);
      Serial.print("CHARS = ");
      Serial.print(chars);
      Serial.print(", SENTENCES = ");
      Serial.print(sentences);
      Serial.print(", CSUM ERR = ");
      Serial.println(failed);
      if (chars == 0) {
        Serial.println("** No characters received from GPS: check wiring **");
      }
    }
  }
}
