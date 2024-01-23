#define NUMBER_OF_REGISTERS 26
#define START_ADDRESS 0x0025
#define DECIMAL_POINT_ADDR 0x0023
struct {
  float phase_voltages[3];
  float phase_currents[3];
  float line_to_line[3];
  float active_power_per_phase[3];
  float reactive_power_per_phase[3];
  float power_factor_per_phase[3];
  float frequency;
} transformer_electrical_data;

struct {
  uint8_t DPT;
  uint8_t DCT;
  uint8_t DPQ;
  uint8_t SIGN;
} decimal_point;

uint8_t result;

int readDecimalPointInfo(){
  result = node.readHoldingRegisters(DECIMAL_POINT_ADDR, 2);
  if(result == node.ku8MBSuccess){
    decimalToHexAndSplit(node.getResponseBuffer(0x00), &decimal_point.DPT, &decimal_point.DCT);
    decimalToHexAndSplit(node.getResponseBuffer(0x01), &decimal_point.DPQ, &decimal_point.SIGN);
//    Serial.println(decimal_point.DPT);
//    Serial.println(decimal_point.DCT);
//    Serial.println(decimal_point.DPQ);
//    Serial.println(decimal_point.SIGN);
    return 1;
  }
  return 0;
}

int readValues(){
  result = node.readHoldingRegisters(START_ADDRESS, NUMBER_OF_REGISTERS);
  if(result == node.ku8MBSuccess){
    //phase voltages
    transformer_electrical_data.phase_voltages[0] = (node.getResponseBuffer(0x00)/10000.00f)*pow(10,decimal_point.DPT);
    transformer_electrical_data.phase_voltages[1] = (node.getResponseBuffer(0x01)/10000.00f)*pow(10,decimal_point.DPT);
    transformer_electrical_data.phase_voltages[2] = (node.getResponseBuffer(0x02)/10000.00f)*pow(10,decimal_point.DPT);

    //line to line
    transformer_electrical_data.line_to_line[0] = (node.getResponseBuffer(0x03)/10000.00f)*pow(10,decimal_point.DPT);
    transformer_electrical_data.line_to_line[1] = (node.getResponseBuffer(0x04)/10000.00f)*pow(10,decimal_point.DPT);
    transformer_electrical_data.line_to_line[2] = (node.getResponseBuffer(0x05)/10000.00f)*pow(10,decimal_point.DPT);

    //phase currents
    transformer_electrical_data.phase_currents[0] = (node.getResponseBuffer(0x06)/10000.00f)*pow(10,decimal_point.DCT);
    transformer_electrical_data.phase_currents[1] = (node.getResponseBuffer(0x07)/10000.00f)*pow(10,decimal_point.DCT);
    transformer_electrical_data.phase_currents[2] = (node.getResponseBuffer(0x08)/10000.00f)*pow(10,decimal_point.DCT);

    //active power per phase
    transformer_electrical_data.active_power_per_phase[0] = (node.getResponseBuffer(0x09)/10000.00f)*pow(10,decimal_point.DPQ);
    transformer_electrical_data.active_power_per_phase[1] = (node.getResponseBuffer(0x0A)/10000.00f)*pow(10,decimal_point.DPQ);
    transformer_electrical_data.active_power_per_phase[2] = (node.getResponseBuffer(0x0B)/10000.00f)*pow(10,decimal_point.DPQ);

    //reactive power per phase
    transformer_electrical_data.reactive_power_per_phase[0] = (node.getResponseBuffer(0x0D)/10000.00f)*pow(10,decimal_point.DPQ);
    transformer_electrical_data.reactive_power_per_phase[1] = (node.getResponseBuffer(0x0E)/10000.00f)*pow(10,decimal_point.DPQ);
    transformer_electrical_data.reactive_power_per_phase[2] = (node.getResponseBuffer(0x0F)/10000.00f)*pow(10,decimal_point.DPQ);

    //power factor per phase
    transformer_electrical_data.power_factor_per_phase[0] = node.getResponseBuffer(0x11)/1000.00f;
    transformer_electrical_data.power_factor_per_phase[1] = node.getResponseBuffer(0x12)/1000.00f;
    transformer_electrical_data.power_factor_per_phase[2] = node.getResponseBuffer(0x13)/1000.00f;

    //frequency
    transformer_electrical_data.frequency = node.getResponseBuffer(0x19)/100.00f;

    return 1;
  }
  return 0;
}



void displayReceivedData(){
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F("-------------------------"));
  Serial.println(F("|\tReceived Data\t|"));
  Serial.println(F("-------------------------"));
  //phase voltages
  Serial.print(F("|\tUa: "));
  Serial.print(transformer_electrical_data.phase_voltages[0]);
  Serial.println(F(" V\t|"));
  Serial.print(F("|\tUb: "));
  Serial.print(transformer_electrical_data.phase_voltages[1]);
  Serial.println(F(" V\t|"));
  Serial.print(F("|\tUc: "));
  Serial.print(transformer_electrical_data.phase_voltages[2]);
  Serial.println(F(" V\t|"));

  //line to line
  Serial.print(F("|\tUab: "));
  Serial.print(transformer_electrical_data.line_to_line[0], 4);
  Serial.println(F(" V\t|"));
  Serial.print(F("|\tUbc: "));
  Serial.print(transformer_electrical_data.line_to_line[1], 4);
  Serial.println(F(" V\t|"));
  Serial.print(F("|\tUca: "));
  Serial.print(transformer_electrical_data.line_to_line[2], 4);
  Serial.println(F(" V\t|"));
  

  //phase currents
  Serial.print(F("|\tIa: "));
  Serial.print(transformer_electrical_data.phase_currents[0], 4);
  Serial.println(F(" A\t|"));
  Serial.print(F("|\tIb: "));
  Serial.print(transformer_electrical_data.phase_currents[1], 4);
  Serial.println(F(" A\t|"));
  Serial.print(F("|\tIc: "));
  Serial.print(transformer_electrical_data.phase_currents[2], 4);
  Serial.println(F(" A\t|"));

  

  //active power per phase
  Serial.print(F("|\tPa: "));
  Serial.print(transformer_electrical_data.active_power_per_phase[0], 4);
  Serial.println(F(" VA\t|"));
  Serial.print(F("|\tPb: "));
  Serial.print(transformer_electrical_data.active_power_per_phase[1], 4);
  Serial.println(F(" VA\t|"));
  Serial.print(F("|\tPc: "));
  Serial.print(transformer_electrical_data.active_power_per_phase[2], 4);
  Serial.println(F(" VA\t|"));
  
  //reactive power per phase
  Serial.print(F("|\tQa: "));
  Serial.print(transformer_electrical_data.reactive_power_per_phase[0], 4);
  Serial.println(F(" VAR\t|"));
  Serial.print(F("|\tQb: "));
  Serial.print(transformer_electrical_data.reactive_power_per_phase[1], 4);
  Serial.println(F(" VAR\t|"));
  Serial.print(F("|\tQc: "));
  Serial.print(transformer_electrical_data.reactive_power_per_phase[2], 4);
  Serial.println(F(" VAR\t|"));
  
  //power factor per phase
  Serial.print(F("|\tPFa: "));
  Serial.print(transformer_electrical_data.power_factor_per_phase[0], 4);
  Serial.println(F(" \t|"));
  Serial.print(F("|\tPFb: "));
  Serial.print(transformer_electrical_data.power_factor_per_phase[1], 4);
  Serial.println(F(" \t|"));
  Serial.print(F("|\tPFc: "));
  Serial.print(transformer_electrical_data.power_factor_per_phase[2], 4);
  Serial.println(F(" \t|"));

  //frequency
  Serial.print(F("|\tF: "));
  Serial.print(transformer_electrical_data.frequency);
  Serial.println(F(" Hz\t|"));
  Serial.println(F("-------------------------"));
  Serial.println(F(""));
}
