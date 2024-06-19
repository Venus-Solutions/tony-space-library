#include <TonyS_X1.h>

void setup() {
  Tony.begin();
  delay(10);
  Tony.pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  Tony.digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  Tony.digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
