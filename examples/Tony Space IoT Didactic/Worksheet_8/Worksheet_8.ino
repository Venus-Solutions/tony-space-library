#include <TonyS_X1.h>
#include <TonyS_X1_ExternalModule.h>

NBIoT nb;

void setup()
{
  Serial.begin(115200);
  Tony.begin();
  Serial.println("\nNBIoT Setting");
  nb.begin(SLOT2);
  Serial.println("NBIoT Ready");
  Serial.print("SIM(S/N) :");
  Serial.println(nb.getSIMSerial());
  Serial.print("IMEI :");
  Serial.println(nb.getIMEI());
  Serial.print("IMSI :");
  Serial.println(nb.getIMSI());
  Serial.print("Network Status:");
  while (!nb.getNetworkStatus())
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("OK");
  Serial.print("Signal :");
  Serial.println(nb.getSignal());
  Serial.print("Signal Strength :");
  Serial.print(nb.getSignaldBm());
  Serial.println("dBm");
  Serial.print("Signal Level :");
  Serial.println(nb.getSignalLevel());
  Serial.print("Device IP :");
  Serial.println(nb.getDeviceIP());
  Serial.println("");
}

void loop()
{
  if (nb.getNetworkStatus()) {
    Serial.print("Signal Strength :");
    Serial.print(nb.getSignaldBm());
    Serial.println("dBm");
    Serial.print("Signal Level :");
    Serial.println(nb.getSignalLevel());
  }
  else {
    Serial.println("Can't be connected to network");
  }
  delay(2000);
}
