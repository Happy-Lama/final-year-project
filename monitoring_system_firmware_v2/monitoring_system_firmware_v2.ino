#include <SoftwareSerial.h>
#include <ModbusMaster.h>

//lora
#define DEVADDR "260B5902"
#define APPSKEY "AE2D4928933D247940297C0DC9F7EC96"
#define NWKSKEY "3F43EFD311ED955076F6974A90D2C8FC"
#define DEVEUI "70B3D57ED0064969"
#define TRANSMISSION_CONFIRMED 0
#define NO_RE_TRANS_TRIALS 1
#define ABP 1
#define DATARATE 4
#define PAYLOAD_LENGTH 199
#define CLASS 0

//modbus
#define RS485_DE 4
#define RS485_RE_NEG 5


#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#define debug_(x) Serial.write(x)
#else
#define debug(x)
#define debugln(x)
#define debug_(x)
#endif

#define GSM_MODE 0


char AT_COMMAND[256];
char payload[PAYLOAD_LENGTH];

uint8_t no_retries = 0;

uint16_t parameters[45];
uint8_t result_;
ModbusMaster node;
//SoftwareSerial modbus(8,7); //Rx, Tx

void serializeData(uint16_t* inputBuffer, char* outputBuffer, int input_length){
  for(byte i = 0; i < input_length - 1; i++){
    sprintf((outputBuffer + i*4), "%04X", inputBuffer[i]);  
  }
  sprintf(outputBuffer, "%s0%d", outputBuffer, inputBuffer[input_length - 1]);
  debugln("");
  debug("Data to be sent: ");
  debugln(outputBuffer);
}

void setup() {
  // put your setup code here, to run once:
//  modbus.begin(9600);
  Serial.begin(38400); //leave low for the modbus, should match the value for the meter
  initRS485();
  if(!GSM_MODE){
    initLoRaModule();
  } else {
    initGSM();
  }
  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int newParameterValues = getParameters(parameters);
  if(newParameterValues == 1){
    no_retries = 0;
    serializeData(parameters, payload, 45);
    if(!GSM_MODE){
      transmitData(payload, PAYLOAD_LENGTH);
    } else {
      sendToServer(payload);
    }
    flashLED();
    delay(60000);
  } else if (newParameterValues == -1){
    no_retries += 1;
    if(no_retries == 5){
      no_retries = 0;
      for(uint8_t i = 0; i < 46; i++){
        parameters[i] = 0;
      }
      serializeData(parameters, payload, 45);
      if(!GSM_MODE){
        transmitData(payload, PAYLOAD_LENGTH);
      } else {
        sendToServer(payload);
        while(Serial.available() > 0){
          Serial.read();
        }
      }
      flashLED();
      
      delay(60000);
    }
  }
}


void flashLED(){
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
