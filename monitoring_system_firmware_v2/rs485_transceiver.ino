//ModbusMaster node;

void preTransmission(){
//  Serial.flush();
  digitalWrite(RS485_DE, HIGH);
  digitalWrite(RS485_RE_NEG, HIGH);
}

void postTransmission(){
  digitalWrite(RS485_DE, LOW);
  digitalWrite(RS485_RE_NEG, LOW);
}

void initRS485() {
  pinMode(RS485_DE, OUTPUT);
  pinMode(RS485_RE_NEG, OUTPUT);

  //power meter baud rate set to 2400
  node.begin(1, Serial); //set power meter id to 1

  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

int getParameters( uint16_t* outputBuffer) {
//  preTransmission();
  result_ = node.readInputRegisters(0x0000, 36);
  
//  postTransmission();
  if(result_ == node.ku8MBSuccess){
    debugln("");
    debugln(F("ParamRead Success!!"));
    for(uint8_t i = 0; i < 36; i++){
      outputBuffer[i] = node.getResponseBuffer(i);
    }
    delay(1000);
//    read line to line voltages
    result_ = node.readInputRegisters(0x00C8, 6);
    if(result_ == node.ku8MBSuccess){
      debugln("");
      debugln(F("LinetoLineRead Success!!"));
      for(uint8_t i = 36; i < 42; i++){
        outputBuffer[i] = node.getResponseBuffer(i-36);
      }
      delay(1000);
//      read frequency
      result_ = node.readInputRegisters(0x0046, 2);
      if(result_ == node.ku8MBSuccess){
        debugln("");
        debugln(F("FrequencyRead Success!!"));
        for(uint8_t i = 42; i < 44; i++){
          outputBuffer[i] = node.getResponseBuffer(i-42);
        }
        outputBuffer[44] = 1;
        debugln("Data storage finished");
        return 1;
      }else {
        return -1;
      }
    }else {
      return -1;
    }
  } else {
    return -1;
  }
}
