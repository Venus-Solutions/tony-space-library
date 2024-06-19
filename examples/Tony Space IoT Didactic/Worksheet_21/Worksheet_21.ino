#include "TonyS_X1.h"
#include "TonyS_X1_ExternalModule.h"

TonySHT31 sht31;
RTC_DS3231 rtc;

int timeout = 0;
//Select your trigger second by 0, 10, 20, 30, 40, 50
int triggerSecond = 40;
String toSend = "";

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
  
  sht31.begin(0x44);
  Tony.begin();
  TonyLORA.slot(SLOT2);
  Serial.println();
}

void loop()
{
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
      now.second() == triggerSecond + 5 ||
      now.second() == triggerSecond + 6 ||
      now.second() == triggerSecond + 7) {
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
    
    if (!isnan(t) && !isnan(h)) {
      int temp = (int)(t * 100);
      int humi = (int)(h * 100);
      toSend = (String)temp + (String)humi;
      
      /* Sending brodcast */
      timeout = 20000;
      if (TonyLORA.sendBrodcast(toSend, timeout) == 1)
      {
        Serial.println("Sending brodcast successfully.");
      }
      else Serial.println("Sending brodcast fail.");
      Serial.println();
      toSend = "";
    }
  }
  delay(1000);
}
