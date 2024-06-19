#include "TonyS_X1.h"

unsigned int currentOutput = 50;

void setup() 
{
  Serial.begin(115200);

  Tony.begin();
}

void loop() 
{
  while(currentOutput < 1024){
    Tony.analogWrite(AIO8, currentOutput);
    currentOutput = currentOutput + 50;
    delay(1000);
  }
  currentOutput = 50;
}
