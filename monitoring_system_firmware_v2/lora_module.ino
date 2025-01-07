//#if GSM_MODE == 0

SoftwareSerial lora(8, 7); //Rx, Tx

void initLoRaModule(){
  lora.begin(9600);
  
  sprintf(AT_COMMAND, "AT+CCLASS=%d", CLASS);
  lora.println(AT_COMMAND);
  delay(1000);
  printToSerial();
  
  sprintf(AT_COMMAND, "AT+CJOINMODE=%d", ABP);
  lora.println(AT_COMMAND);
  delay(1000);
  printToSerial();

  sprintf(AT_COMMAND, "AT+CDEVADDR=%s", DEVADDR);
  lora.println(AT_COMMAND);
  delay(1000);
  printToSerial();

  sprintf(AT_COMMAND, "AT+CAPPSKEY=%s", APPSKEY);
  lora.println(AT_COMMAND);
  delay(1000);
  printToSerial();

  sprintf(AT_COMMAND, "AT+CNWKSKEY=%s", NWKSKEY);
  lora.println(AT_COMMAND);
  delay(1000);
  printToSerial();

  sprintf(AT_COMMAND, "AT+CDEVEUI=%s", DEVEUI);
  lora.println(AT_COMMAND);
  delay(1000);
  printToSerial();

  sprintf(AT_COMMAND, "AT+CDATARATE=%s", DATARATE);
  lora.println(AT_COMMAND);
  delay(1000);
  printToSerial();
  
}

void transmitData(char* payload, int payload_length){
  sprintf(AT_COMMAND, "AT+DTRX=%d,%d,%d,%s", TRANSMISSION_CONFIRMED, NO_RE_TRANS_TRIALS, payload_length, payload);
  debugln(AT_COMMAND);
  lora.println(AT_COMMAND);
  delay(3000);
  printToSerial();
}

void printToSerial(){
  while(lora.available()){
    debug((char)lora.read());
  }
  debugln();
}

//#else
//void initLoRaModule(){};
//void printToSerial(){};
//void transmitData(char* payload, int payload_length){};
//#endif
