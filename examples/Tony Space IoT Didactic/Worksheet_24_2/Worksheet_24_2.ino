#include "TonyS_X1.h"
#include "TonyS_X1_ExternalModule.h"

#define SLAVE_ID 0x01
#define ADDRESS  100

Tony_Modbus_Master modbus;

void setup() 
{
  Serial.begin(115200);
  Tony.begin();
  
  modbus.setSlot(SLOT4);
  modbus.begin(115200);
}
void loop() 
{
 Serial.print("Read SingleHoldingRegister : ");
 Serial.println(modbus.readSingleHoldingRegister(SLAVE_ID, ADDRESS));
 delay(1000);
}
