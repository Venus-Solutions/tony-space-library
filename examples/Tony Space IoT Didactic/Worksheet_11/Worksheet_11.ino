#include <TonyS_X1.h>
#include <TonyS_X1_ExternalModule.h>

TonyTFT tft = TonyTFT(SLOT1);
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup(void) {
  Serial.begin(115200);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  Tony.begin();
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  tft.init(240, 240);
  tft.setRotation(3);
}

void loop() {
  tft.setCursor(0, 0);
  tft.fillScreen(BLACK);
  tft.setTextSize(4);
  tft.setTextColor(GREEN);
  DateTime now = rtc.now();
  tft.println(daysOfTheWeek[now.dayOfTheWeek()]);
  tft.println("");
  tft.setTextSize(3);
  tft.setTextColor(CYAN);
  tft.print(now.day(), DEC);
  tft.print('/');
  tft.print(now.month(), DEC);
  tft.print('/');
  tft.println(now.year(), DEC);
  tft.println("");
  tft.setTextSize(5);
  tft.setTextColor(WHITE);
  tft.print(now.hour(), DEC);
  tft.print(':');
  tft.print(now.minute(), DEC);
  tft.print(':');
  tft.println(now.second(), DEC);
  delay(1000);
}
