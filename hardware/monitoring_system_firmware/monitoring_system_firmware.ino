#include <ModbusMaster.h>

#define RS485_DE 4
#define RS485_RE_NEG 5

ModbusMaster node;

void preTransmission(){
  digitalWrite(RS485_DE, HIGH);
  digitalWrite(RS485_RE_NEG, HIGH);
}

void postTransmission(){
  digitalWrite(RS485_DE, LOW);
  digitalWrite(RS485_RE_NEG, LOW);
}


void setup() {
  // put your setup code here, to run once:
  pinMode(RS485_DE, OUTPUT);
  pinMode(RS485_RE_NEG, OUTPUT);

  //power meter baud rate set to 9600
  Serial.begin(9600);

  node.begin(1, Serial); //set power meter id to 1


  //configure the pre and post Transmission functions correctly
  //crucial as it will affect the communication
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}




void loop() {
  // put your main code here, to run repeatedly:
  int success = readValues();
  delay(1000);
  if(success){
    displayReceivedData();
    delay(15000);
  }  
}
