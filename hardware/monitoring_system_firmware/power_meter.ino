#define NUMBER_OF_REGISTERS 26
#define START_ADDRESS 0x0025

struct {
  float phase_voltages[3];
  float phase_currents[3];
  float line_to_line[3];
  float active_power_per_phase[3];
  float reactive_power_per_phase[3];
  float power_factor_per_phase[3];
  float frequency;
} transformer_electrical_data;


uint8_t result;

int readValues(){
  result = node.readHoldingRegisters(START_ADDRESS, NUMBER_OF_REGISTERS);
  if(result == node.ku8MBSuccess){
    //phase voltages
    transformer_electrical_data.phase_voltages[0] = node.getResponseBuffer(0x00)/10.00f;
    transformer_electrical_data.phase_voltages[1] = node.getResponseBuffer(0x01)/10.00f;
    transformer_electrical_data.phase_voltages[2] = node.getResponseBuffer(0x02)/10.00f;

    //line to line
    transformer_electrical_data.line_to_line[0] = node.getResponseBuffer(0x03)/10.00f;
    transformer_electrical_data.line_to_line[1] = node.getResponseBuffer(0x04)/10.00f;
    transformer_electrical_data.line_to_line[2] = node.getResponseBuffer(0x05)/10.00f;

    //phase currents
    transformer_electrical_data.phase_currents[0] = node.getResponseBuffer(0x06)/10.00f;
    transformer_electrical_data.phase_currents[1] = node.getResponseBuffer(0x07)/10.00f;
    transformer_electrical_data.phase_currents[2] = node.getResponseBuffer(0x08)/10.00f;

    //active power per phase
    transformer_electrical_data.active_power_per_phase[0] = node.getResponseBuffer(0x09)/10.00f;
    transformer_electrical_data.active_power_per_phase[1] = node.getResponseBuffer(0x0A)/10.00f;
    transformer_electrical_data.active_power_per_phase[2] = node.getResponseBuffer(0x0B)/10.00f;

    //reactive power per phase
    transformer_electrical_data.reactive_power_per_phase[0] = node.getResponseBuffer(0x0D)/10.00f;
    transformer_electrical_data.reactive_power_per_phase[1] = node.getResponseBuffer(0x0E)/10.00f;
    transformer_electrical_data.reactive_power_per_phase[2] = node.getResponseBuffer(0x0F)/10.00f;

    //power factor per phase
    transformer_electrical_data.power_factor_per_phase[0] = node.getResponseBuffer(0x11)/10.00f;
    transformer_electrical_data.power_factor_per_phase[1] = node.getResponseBuffer(0x12)/10.00f;
    transformer_electrical_data.power_factor_per_phase[2] = node.getResponseBuffer(0x13)/10.00f;

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
  Serial.print(transformer_electrical_data.line_to_line[0]);
  Serial.println(F(" V\t|"));
  Serial.print(F("|\tUbc: "));
  Serial.print(transformer_electrical_data.line_to_line[1]);
  Serial.println(F(" V\t|"));
  Serial.print(F("|\tUca: "));
  Serial.print(transformer_electrical_data.line_to_line[2]);
  Serial.println(F(" V\t|"));
  

  //phase currents
  Serial.print(F("|\tIa: "));
  Serial.print(transformer_electrical_data.phase_currents[0]);
  Serial.println(F(" A\t|"));
  Serial.print(F("|\tIb: "));
  Serial.print(transformer_electrical_data.phase_currents[1]);
  Serial.println(F(" A\t|"));
  Serial.print(F("|\tIc: "));
  Serial.print(transformer_electrical_data.phase_currents[2]);
  Serial.println(F(" A\t|"));

  

  //active power per phase
  Serial.print(F("|\tPa: "));
  Serial.print(transformer_electrical_data.active_power_per_phase[0]);
  Serial.println(F(" kva\t|"));
  Serial.print(F("|\tPb: "));
  Serial.print(transformer_electrical_data.active_power_per_phase[1]);
  Serial.println(F(" kva\t|"));
  Serial.print(F("|\tPc: "));
  Serial.print(transformer_electrical_data.active_power_per_phase[2]);
  Serial.println(F(" kva\t|"));
  
  //reactive power per phase
  Serial.print(F("|\tQa: "));
  Serial.print(transformer_electrical_data.reactive_power_per_phase[0]);
  Serial.println(F(" kvar\t|"));
  Serial.print(F("|\tQb: "));
  Serial.print(transformer_electrical_data.reactive_power_per_phase[1]);
  Serial.println(F(" kvar\t|"));
  Serial.print(F("|\tQc: "));
  Serial.print(transformer_electrical_data.reactive_power_per_phase[2]);
  Serial.println(F(" kvar\t|"));
  
  //power factor per phase
  Serial.print(F("|\tPFa: "));
  Serial.print(transformer_electrical_data.power_factor_per_phase[0]);
  Serial.println(F(" %\t|"));
  Serial.print(F("|\tPFb: "));
  Serial.print(transformer_electrical_data.power_factor_per_phase[1]);
  Serial.println(F(" %\t|"));
  Serial.print(F("|\tPFc: "));
  Serial.print(transformer_electrical_data.power_factor_per_phase[2]);
  Serial.println(F(" %\t|"));

  //frequency
  Serial.print(F("|\tF: "));
  Serial.print(transformer_electrical_data.frequency);
  Serial.println(F(" Hz\t|"));
  Serial.println(F("-------------------------"));
  Serial.println(F(""));
}
