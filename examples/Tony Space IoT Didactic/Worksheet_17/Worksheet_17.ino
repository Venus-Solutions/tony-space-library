#include <TonyS_X1.h>
#include <TonyS_X1_ExternalModule.h>

int sizeFRAM = 0;
long message[] = {
  0x1111AAAA,
  0x2222BBBB,
  0x3333CCCC,
  0x4444DDDD
};
long readData[10];

void setup()
{
  Serial.begin(115200);
  Tony.begin();
  TonyFRAM.clear();
  for (int i = 0; i < sizeof(message); i++) {
    sizeFRAM = TonyFRAM.size(4);
    if (sizeFRAM < 512) {
      TonyFRAM.write(sizeFRAM, message[i]);
    }
    else {
      Serial.println("Data is Full");
      while (1);
    }
    delay(100);
  }
  sizeFRAM = TonyFRAM.size(4);
  for (int j = 0; j < sizeFRAM / 4; j++) {
    sizeFRAM = TonyFRAM.size(4);
    readData[j] = TonyFRAM.read(j * 4);
    delay(100);
  }
  Serial.println("");
  for (int k = 0; k < sizeFRAM / 4; k++) {
    Serial.print("message[");
    Serial.print(k);
    Serial.print("] : ");
    Serial.println(readData[k], HEX);
  }
}

void loop()
{
}
