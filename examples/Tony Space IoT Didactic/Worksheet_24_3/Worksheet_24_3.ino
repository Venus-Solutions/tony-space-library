#include "TonyS_X1.h"
#include "TonyS_X1_ExternalModule.h"

#define SLAVE_ID 15
#define ADDRESS  403

Tony_Modbus_Master modbus;

unsigned int data = 0;

void setup() 
{
  Serial.begin(115200);
  Tony.begin();

  modbus.setSlot(SLOT4);
  modbus.begin(115200);
}

void loop() 
{
  modbus.presetSingleRegister(SLAVE_ID, ADDRESS, data);
  data++;
  delay(500);
}
