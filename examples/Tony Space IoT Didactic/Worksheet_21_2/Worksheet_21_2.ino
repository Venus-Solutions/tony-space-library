#include "TonyS_X1.h"
#include "TonyS_X1_ExternalModule.h"

RTC_DS3231 rtc;

int timeout = 0;
//Select your trigger second by 0, 10, 20, 30, 40, 50
int triggerSecond = 40;
char charbuff[40];
String stringbuff;

void setup() {
  Serial.begin(115200);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  Tony.begin();
  TonyLORA.slot(SLOT2);
  Serial.println();
}

void loop() {
  DateTime now = rtc.now();
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  
  if (now.second() == triggerSecond ||
      now.second() == triggerSecond + 1 ||
      now.second() == triggerSecond + 2 ||
      now.second() == triggerSecond + 3 ||
      now.second() == triggerSecond + 4 ||
      now.second() == triggerSecond + 5) {
        
    /* receiving brodcast */
    timeout = 5000;
    if (TonyLORA.receiveBrodcast(charbuff, timeout) == 1)
    {
      Serial.print("Data : ");
      stringbuff = charbuff;
      Serial.println(stringbuff);
      
      String temp = stringbuff.substring(9, 13);
      float temp_f = temp.toInt() / 100.00;
      Serial.print("temp = ");
      Serial.print(temp_f);
      Serial.println(" *C");
      
      String humi = stringbuff.substring(13, 17);
      float humi_f = humi.toInt() / 100.00;
      Serial.print("humi = ");
      Serial.print(humi_f);
      Serial.println(" %");
    }
    else Serial.println("Receiving brodcast fail.");
    charbuff[0] = '\0';
  }
  delay(1000);
}
