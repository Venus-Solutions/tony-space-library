#include <TonyS_X1.h>
#include <TonyS_X1_ExternalModule.h>

HardwareSerial HWSerial(NULL);

void setup() {
  Serial.begin(115200);
  Tony.begin();
  HWSerial = Tony.SerialBegin(SLOT4, 115200);
}
void loop() {
  if(HWSerial.available())
    Serial.write(HWSerial.read());
  if(Serial.available())
    HWSerial.write(Serial.read());
}
