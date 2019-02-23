// Shimble Board ///////////////////////////////////////////////////////////////////////////////////////
    // Main .cpp File
//
// Created for 2019 Valkyrie by: Andrew Phillips, ajpnq2
//
// Libraries ///////////////////////////////////////////////////////////////////////////////////////////
#include "ShimbleBoard_Software.h"

RoveCommEthernetUdp RoveComm; //Extantiates RoveComm class

// Setup & Loop Funcitons //////////////////////////////////////////////////////////////////////////////

void shimbleSetup() //void setup
{
  Serial.begin(9600);
  RoveComm.begin(RC_SHIMBLENAVBOARD_FOURTHOCTET);
  delay(ROVECOMM_DELAY);

  Servos[0].attach(SERVO_1_CRTL_PIN);
  Servos[1].attach(SERVO_2_CRTL_PIN);
  Servos[2].attach(SERVO_3_CRTL_PIN);
  Servos[3].attach(SERVO_4_CRTL_PIN);
  Servos[4].attach(SERVO_5_CRTL_PIN);
  Servos[5].attach(SERVO_6_CRTL_PIN);
  Servos[6].attach(SERVO_7_CRTL_PIN);
  Servos[7].attach(SERVO_8_CRTL_PIN);

  for (int i = 0; i < 8; i++)
  {
    Servos[i].write(0);
  }
}

void shimbleLoop(rovecomm_packet) //void loop
{ 
  rovecomm_packet packet;
  RC_SHIMBLEBOARD_SERVOPOS_DATATYPE servo_posotions[RC_SHIMBLEBOARD_SERVOPOS_DATACOUNT];

  for (int i = 0; i < RC_SHIMBLEBOARD_SERVOPOS_DATACOUNT; i++)
  {
    servo_positions[i] = Servos[i].read();
  }
  
  packet = RoveComm.read();

  if(packet.data_id != 0)
  {
    switch (packet.data_id)
    {
      case RC_SHIMBLEBOARD_SERVOINC_DATAID:
      {
        for (int i = 0; i < RC_SHIMBLEBOARD_SERVOINC_DATACOUNT; i++)
        {
           Servos[i].write(servo_positions[i] + packet.data[i]);
        }
        break;
      }

      case RC_SHIMBLEBOARD_SERVOTOPOS_DATAID:
      {
        for (int i = 0; i < RC_SHIMBLEBOARD_SERVOTOPOS_DATACOUNT; i++)
        {
           Servos[i].write(packet.data[i]);
        }
        break;    
      }

      /*case RC_SHIMBLEBOARD_SERVOTOSETPOS_DATAID:
      {
        for (int i = 0; i < RC_SHIMBLEBOARD_SERVOTOSETPOS_DATACOUNT; i++)
        {
           Servos[i].write( enum value? );
        }
        break; 
      } */
    }
  }

  if (millis() - telemetry_time >= 1000) // If it's been more than 1 second since telemetry was sent,
  {                                      // send telemetry and update telemetry_time
    telemetry_time = millis();
    RoveComm.write(RC_SHIMBLEBOARD_SERVOPOS_DATAID, RC_SHIMBLEBOARD_SERVOPOS_DATACOUNT, servo_positions);
    delay(ROVECOMM_DELAY);
  }
}
