#include "TonyS_X1.h"
#include "TonyS_X1_ExternalModule.h"

T4_20mA  T4_20mA(SLOT6);

unsigned int inputVal = 0;
float milliAmp = 0;
                
void setup() 
{
  Serial.begin(115200);

  Tony.begin();
}

void loop() 
{
  inputVal = T4_20mA.readValue();
  Serial.print("Input Value = ");
  Serial.println(inputVal); 

  //----- Convert inputVal to mA ------//

  milliAmp = inputVal/62.30;                // 1mA = 62.30   Calculate analog to voltage        
  Serial.print("Current Input = ");
  Serial.print(milliAmp, 3);  
  Serial.println(" mA");  
  Serial.println();  
  delay(500); 
}
