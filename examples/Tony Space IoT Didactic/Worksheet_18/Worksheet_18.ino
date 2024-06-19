#include <TonyS_X1.h>
#include <TonyS_X1_ExternalModule.h>

void setup()
{
  Serial.begin(115200);
  Tony.begin();
  TonyPM.slot(SLOT1);
  TonyPM.begin();
}

void loop()
{
  TonyPM.read();
  if (TonyPM)
  {
    Serial.printf("PM1.0=%2d, PM2.5=%2d, PM10=%2d [ug/m3]\n",
                  TonyPM.pm01, TonyPM.pm25, TonyPM.pm10);
  }
  else
  {
    switch (TonyPM.status)
    {
      case TonyPM.OK:
        break;
      case TonyPM.ERROR_TIMEOUT:
        Serial.println(F(PMS_ERROR_TIMEOUT));
        break;
      case TonyPM.ERROR_MSG_UNKNOWN:
        Serial.println(F(PMS_ERROR_MSG_UNKNOWN));
        break;
      case TonyPM.ERROR_MSG_HEADER:
        Serial.println(F(PMS_ERROR_MSG_HEADER));
        break;
      case TonyPM.ERROR_MSG_BODY:
        Serial.println(F(PMS_ERROR_MSG_BODY));
        break;
      case TonyPM.ERROR_MSG_START:
        Serial.println(F(PMS_ERROR_MSG_START));
        break;
      case TonyPM.ERROR_MSG_LENGTH:
        Serial.println(F(PMS_ERROR_MSG_LENGTH));
        break;
      case TonyPM.ERROR_MSG_CKSUM:
        Serial.println(F(PMS_ERROR_MSG_CKSUM));
        break;
      case TonyPM.ERROR_PMS_TYPE:
        Serial.println(F(PMS_ERROR_PMS_TYPE));
        break;
    }
  }
  Serial.println();
  delay(3000);
}
