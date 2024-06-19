#include <TonyS_X1.h>
#include <TonyS_X1_ExternalModule.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

#define FIREBASE_HOST "Your Firebase URL"
#define FIREBASE_AUTH "Your Firebase Authentication"

const char* ssid     =  "Your ssid";               
const char* password =  "Your password";   

FirebaseData firebaseData;
float value = 0.0;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  Tony.begin();

  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  
  Firebase.setFloat(firebaseData, "data", value);
  
  Serial.print("data");
  Serial.print(" = ");
  Serial.println(value);
  
  value += 0.1;
  if(value > 100.0)value = 0.0;  

  delay(1000);
}
