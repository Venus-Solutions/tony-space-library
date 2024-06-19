#include <TonyS_X1.h>
#include <TonyS_X1_ExternalModule.h>

TonySHT31 sht31;

void setup() {
  Serial.begin(115200);
  Tony.begin();
  sht31.begin(0x44);
}

void loop()
{
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();
  if (!isnan(t)) {
    Serial.print("Temperature = ");
    Serial.print(t);
    Serial.println(" *C");
  }
  else {
    Serial.println("Failed to read temperature");
  }
  if (!isnan(h)) {
    Serial.print("Humidity = ");
    Serial.print(h);
    Serial.println(" %");
  }
  else {
    Serial.println("Failed to read humidity");
  }
  Serial.println();
  delay(1000);
}
