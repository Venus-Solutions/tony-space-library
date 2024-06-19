#include <TonyS_X1.h>
#include <TonyS_X1_ExternalModule.h>

TONY_ADXL345 TonyAc;

void setup() {
  Serial.begin(115200);
  Tony.begin();
  TonyAc.powerOn();
}

void loop() {
  int x, y, z;
  TonyAc.readXYZ(&x, &y, &z);
  Serial.print("values of X = ");
  Serial.println(x);
  Serial.print("values of Y = ");
  Serial.println(y);
  Serial.print("values of Z = ");
  Serial.println(z);
  double xyz[3];
  double ax, ay, az;
  TonyAc.getAcceleration(xyz);
  ax = xyz[0];
  ay = xyz[1];
  az = xyz[2];
  Serial.print("Acceleration in X = ");
  Serial.print(ax);
  Serial.println(" g");
  Serial.print("Acceleration in Y = ");
  Serial.print(ay);
  Serial.println(" g");
  Serial.print("Acceleration in Z = ");
  Serial.print(az);
  Serial.println(" g");
  Serial.println("******************************");
  delay(500);
}
