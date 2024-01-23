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
  //phase voltages
  Serial.print(F("Ua: "));
  Serial.println(transformer_electrical_data.phase_voltages[0]);
  Serial.print(F("Ub: "));
  Serial.println(transformer_electrical_data.phase_voltages[1]);
  Serial.print(F("Uc: "));
  Serial.println(transformer_electrical_data.phase_voltages[2]);

  //line to line
  Serial.print(F("Uab: "));
  Serial.println(transformer_electrical_data.line_to_line[0]);
  Serial.print(F("Ubc: "));
  Serial.println(transformer_electrical_data.line_to_line[1]);
  Serial.print(F("Uca: "));
  Serial.println(transformer_electrical_data.line_to_line[2]);

  //phase currents
  Serial.print(F("Ia: "));
  Serial.println(transformer_electrical_data.phase_currents[0]);
  Serial.print(F("Ib: "));
  Serial.println(transformer_electrical_data.phase_currents[1]);
  Serial.print(F("Ic: "));
  Serial.println(transformer_electrical_data.phase_currents[2]);

  //active power per phase
  Serial.print(F("Pa: "));
  Serial.println(transformer_electrical_data.active_power_per_phase[0]);
  Serial.print(F("Pb: "));
  Serial.println(transformer_electrical_data.active_power_per_phase[1]);
  Serial.print(F("Pc: "));
  Serial.println(transformer_electrical_data.active_power_per_phase[2]);

  //reactive power per phase
  Serial.print(F("Qa: "));
  Serial.println(transformer_electrical_data.reactive_power_per_phase[0]);
  Serial.print(F("Qb: "));
  Serial.println(transformer_electrical_data.reactive_power_per_phase[1]);
  Serial.print(F("Qc: "));
  Serial.println(transformer_electrical_data.reactive_power_per_phase[2]);

  //power factor per phase
  Serial.print(F("PFa: "));
  Serial.print(transformer_electrical_data.power_factor_per_phase[0]);
  Serial.println(F("%"));
  Serial.print(F("PFb: "));
  Serial.print(transformer_electrical_data.power_factor_per_phase[1]);
  Serial.println(F("%"));
  Serial.print(F("PFc: "));
  Serial.print(transformer_electrical_data.power_factor_per_phase[2]);
  Serial.println(F("%"));

  //frequency
  Serial.print(F("F: "));
  Serial.println(transformer_electrical_data.frequency);
}
