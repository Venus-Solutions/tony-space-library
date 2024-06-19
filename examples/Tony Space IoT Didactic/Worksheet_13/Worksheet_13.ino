#include <TonyS_X1.h>

void setup() {
  Serial.begin(115200);
  Tony.begin();
  Tony.pinMode(IO10, INPUT_PULLUP);
}

void loop() {
  bool value = Tony.digitalRead(IO10);
  Serial.print("value : ");
  Serial.println(value);
  delay(1000);
}
