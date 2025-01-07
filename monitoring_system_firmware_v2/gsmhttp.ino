//#if GSM_MODE == 1

#include <ArduinoJson.h>
SoftwareSerial gsm(9, 10);
StaticJsonDocument<300> object;
char sendtoserver[256];

void initGSM(){
  gsm.begin(9600);

  debugln(F("Initializing GSM Module..."));
  gsm.println("AT");
  delay(1000);
  showSerialData();
  
  gsm.println(F("AT+CMEE=1"));
  delay(15000);

  debugln(F("Setting up internet connection..."));
  gsm.println(F("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""));
  delay(2000);
  showSerialData();

  gsm.println(F("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\""));
  delay(6000);
  showSerialData();
  
  gsm.println(F("AT+SAPBR=1,1"));
  delay(6000);
  showSerialData();

  gsm.println(F("AT+SAPBR=2,1"));
  delay(2500);
  showSerialData();

  debugln(F("Done"));
}

void sendToServer(char * message){
  debugln(strlen(message));
  gsm.println(F("AT+HTTPINIT"));
  delay(1000);
  showSerialData();

  gsm.println(F("AT+HTTPPARA=\"CID\",1"));
  delay(2000);
  showSerialData();

  
//  int age = 13;
//  char name_[] = "Leon";
  
  object["devEUI"] = DEVEUI;

  delay(1000);
  object["payload"] = message;
  delay(1000);
  
//  debugln(object["devEUI"]);
//  serializeJson(object, Serial);
//  delay(1000);
  
//  sprintf(sendtoserver, "{\"devEUI\":\"%s\",\"payload\":\"%s\"}", DEVEUI, message);
  serializeJson(object, sendtoserver);
  debugln(sendtoserver);
  delay(200);
  showSerialData();

//  Serial.pri
  gsm.println(F("AT+HTTPPARA=\"URL\",\"143.198.151.156/post-data\""));
  delay(2000);
  showSerialData();

  gsm.println(F("AT+HTTPPARA=\"REDIR\",1"));
  delay(2000);
  showSerialData();

  gsm.println(F("AT+HTTPSSL=0"));
  delay(2500);
  showSerialData();

  gsm.println(F("AT+HTTPPARA=\"CONTENT\",\"application/json\""));
  delay(200);
  showSerialData();

  gsm.println("AT+HTTPDATA="+String(strlen(sendtoserver))+",100000");
//  Serial.println(sendtoserver);
  delay(200);
  showSerialData();

  gsm.println(sendtoserver);
  delay(200);
  showSerialData();

  gsm.println(F("AT+HTTPACTION=1"));
  delay(10000);
  showSerialData();

  gsm.println(F("AT+HTTPREAD"));
  delay(6000);
  showSerialData();

  gsm.println(F("AT+HTTPTERM"));
  delay(6000);
  showSerialData();
  delay(10000);
}

void showSerialData(){
  while(gsm.available() != 0){
    debug_(gsm.read());
    delay(10);
  }
  delay(1000);
}
////#else
//void initGSM(){};
//void sendToServer(char * message){};
//#endif
