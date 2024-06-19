#include <TonyS_X1.h>
#include <TonyS_X1_ExternalModule.h>

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
  now = millis();
  if (now - lastMeasure > interval) {
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
      Serial.print("LATITUDE = ");
      if (flat == TonyGPS.GPS_INVALID_F_ANGLE) {
        Serial.print(0.0);
      }
      else {
        Serial.print(flat, 6);
      }
      Serial.print(", LONGITUDE = ");
      if (flon == TonyGPS.GPS_INVALID_F_ANGLE) {
        Serial.print(0.0);
      }
      else {
        Serial.print(flon, 6);
      }
    }
    TonyGPS.stats(&chars, &sentences, &failed);
    Serial.print(", CHARS = ");
    Serial.print(chars);
    Serial.print(", SENTENCES = ");
    Serial.print(sentences);
    Serial.print(", CSUM ERR = ");
    Serial.println(failed);
    if (chars == 0) {
      Serial.println("** No characters received from GPS:check wiring **");
    }
  }
}
