#include "Arduino.pb.h" 
#include "pb_common.h"
#include "pb.h"
#include "pb_encode.h"
#include"string.h"
#include"cobs.h"
#include "pb_decode.h"

float Temp1 = 23.69;
float Temp2 = 23.85;
float Curr1 = 0.07;
float Curr2 = 0.06;
float Curr3 = 0.64;
bool DAQ_flag = false;
float BattVolt = 15.11;
char state[128] = "READY";
int switch1 = 0;
int switch2 = 0;
int PWM1 = 1052;
int PWM2 = 1001;
bool Hflag = true; 
bool ADD_ZERO_BYTE = true;
char user[3] = "r";
int incoming;
int i = 0, flag = 0;

void setup() {
 
  Serial.begin(9600);

}

void loop() {

 // i = 0;
  uint8_t buffer[100];

  uint8_t bufferk[30];
  uint8_t bufferm[30];
  
  size_t msg_len;
  Data message = Data_init_zero;
 

  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  message.Temp1 = Temp1;
  message.Temp2 = Temp2;
  message.Curr1 = Curr1;
  message.Curr2 = Curr2;
  message.Curr3 = Curr3;
  message.DAQ_flag = DAQ_flag;
  message.BattVolt = BattVolt;
  strcpy(message.state, state);
  message.switch1 = switch1;
  message.switch2 = switch2;
  message.PWM1 = PWM1;
  message.PWM2 = PWM2;
  message.Hflag = Hflag;
  strcpy(message.user, user);
  message.Sflag = true;

  bool status = pb_encode(&stream, Data_fields, &message);

  if (!status)
  {
      Serial.println("Failed to encode");
      return;
  }

  size_t ENCODED_MESSAGE_SIZE = getCOBSBufferSize(stream.bytes_written, ADD_ZERO_BYTE);

    // Allocate buffer big enough to hold result of COBS encoding.
  uint8_t cobs_buffer[ENCODED_MESSAGE_SIZE] = {0};
  size_t cobs_buffer_size = sizeof(cobs_buffer);
 

  size_t encoded_size = encodeCOBS(buffer, stream.bytes_written, cobs_buffer, cobs_buffer_size, ADD_ZERO_BYTE);
  Serial.write(cobs_buffer, encoded_size);
 // delay(500);
   
  Temp1 = Temp1 + 0.01;
  Temp2 = Temp2 + 0.01;
  // Curr1 = Curr1 + 0.002;
  // Curr2 = Curr2 + 0.002;
  // Curr3 = Curr3 + 0.002;
  //BattVolt = BattVolt + 0.01;  

  while(Serial.available())
  {
    bufferk[i] = Serial.read();
    i++;
    flag = 1;
    
    }
   
  if(flag == 1){  
    command messagek = command_init_zero;
    pb_istream_t streamk = pb_istream_from_buffer(bufferk, sizeof(bufferk));
    bool statusi = pb_decode(&streamk, command_fields, &messagek); 

    commandAck messages = commandAck_init_zero;
    if(messagek.commandtype != 0){
     
     messages.statuss = 1;
    }

    else{
      messages.statuss = 0;
    }

     pb_ostream_t streams = pb_ostream_from_buffer(bufferm, sizeof(bufferm));
     bool statuss = pb_encode(&streams, commandAck_fields, &messages);
     
      if (!statuss)
      {
      Serial.println("Failed to encode");
      return;
      }
              
      
      size_t ENCODED_MESSAGE_SIZEm = getCOBSBufferSize(streams.bytes_written, ADD_ZERO_BYTE);

     // Allocate buffer big enough to hold result of COBS encoding.
       uint8_t cobs_bufferm[ENCODED_MESSAGE_SIZEm] = {0};
      size_t cobs_buffer_sizem = sizeof(cobs_bufferm);
 

      size_t encoded_sizem = encodeCOBS(bufferm, streams.bytes_written, cobs_bufferm, cobs_buffer_sizem, ADD_ZERO_BYTE);

      Serial.write(cobs_bufferm, encoded_sizem); 

      flag = 0;   
    
  
  }
}
  
