#include <TonyS_X1.h>
#include <TonyS_X1_ExternalModule.h>

EC25_HTTP http;
int ret;
unsigned char buff[100];
unsigned char textlength;

void setup() {
  Serial.begin(115200);
  Tony.begin();
  LTE.initial(SLOT2);
  Serial.println("Power On 4G Module Wait Ready...");
  LTE.powerOn(true);
  LTE.waitModuleReady(20);
  Serial.print("IMEI: ");
  Serial.println(LTE.getIMEI());
  Serial.print("Network :");
  while (!LTE.getNetworkRegis())
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Ready");
  Serial.print("Operator: ");
  Serial.println(LTE.getOperator());
  Serial.print("Signal: ");
  Serial.println(String(LTE.getSignaldBm()) + " dBm");
  Serial.print("Connect Internet: ");
  Serial.println(LTE.connectInternet() ? "OK" : "Fail");
  Serial.print("IP Address: ");
  Serial.println(LTE.getIPAddress());
}

void loop()
{
  Serial.print("Set URL :");
  ret = http.setURL("http://covid19.th-stat.com/api/open/today");
  if (ret)
  {
    Serial.println("OK");
    Serial.print("GET: ");
    ret = http.get();
    Serial.println(ret);
    if (ret == 200)
    {
      while (textlength = http.read(buff, 100))
      {
        Serial.write(buff, textlength);
      }
      Serial.println("\r\n==========Finish==========\r\n");
    }
  }
  else {
    Serial.print("Error");
  }
  delay(1000);
}
