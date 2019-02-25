// Shimble Board ///////////////////////////////////////////////////////////////////////////////////////
    // Main .cpp File
//
// Created for 2019 Valkyrie by: Andrew Phillips, ajpnq2
//
// Libraries ///////////////////////////////////////////////////////////////////////////////////////////
#include "ShimbleBoard_Software.h"
#include "RoveComm.h"
#include <Energia.h>

#define RED_MAX_REVERSE -1025
#define RED_MAX_FORWARD 1025
#define CONTINUOUS_MAX_REVERSE 83
#define CONTINUOUS_MAX_FORWARD 103

// Variable Declarations ///////////////////////////////////////////////////////////////////////////////
Servo Servos[8];
uint16_t servo_positions[8];
uint32_t telemetry_time = 0;

// Setup & Loop Funcitons //////////////////////////////////////////////////////////////////////////////

void shimbleSetup() //void setup
{
  Serial.begin(9600);

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
    Servos[i].write(93);
  }


  Serial.println("Shimble Setup Complete.");
}

void shimbleLoop(rovecomm_packet packet, RoveCommEthernetUdp * RoveComm) //void loop
{ 
  /*
  while(1)
  {
    for (int j = 0; j<180; j+=1)

    {
       for (int i = 0; i < 8; i++)
        {
          Servos[i].write(j);//Our Range is (60, 120) where 90 is full stop, 60 is full CW, and 120 is full CCW
        }
        Serial.println(j);
        delay(500);
    }   
  }
  */
  
  RC_SHIMBLEBOARD_SERVOPOS_DATATYPE servo_posotions[RC_SHIMBLEBOARD_SERVOPOS_DATACOUNT];

  for (int i = 0; i < RC_SHIMBLEBOARD_SERVOPOS_DATACOUNT; i++)
  {
    servo_positions[i] = Servos[i].read();
  }
  
  //Servos[0].write(93);
  //Servos[1].write(90);

  if(packet.data_id != 0)
  {
    switch (packet.data_id)
    {
      case RC_SHIMBLEBOARD_SERVOINC_DATAID: //Servo Increment
      {
        for (int i = 0; i < RC_SHIMBLEBOARD_SERVOINC_DATACOUNT; i++)
        {
           //Servos[i].write(servo_positions[i] + packet.data[i]);
        }
        break;
      }

      case RC_SHIMBLEBOARD_MAINGBIMALINC_DATAID: //Main Gimbal Increment
      {
		Servos[0].write(map(packet.data[0], RED_MAX_REVERSE, RED_MAX_FORWARD, CONTINUOUS_MAX_REVERSE, CONTINUOUS_MAX_FORWARD));
		Servos[1].write(map(packet.data[1], RED_MAX_REVERSE, RED_MAX_FORWARD, CONTINUOUS_MAX_REVERSE, CONTINUOUS_MAX_FORWARD));
        Serial.println("IN");
        
		
		break;
      }

      case RC_SHIMBLEBOARD_DRIVEGBIMALINC_DATAID: //Drive Gimbal Increment
      {
        Servos[2].write(map(packet.data[0], RED_MAX_REVERSE, RED_MAX_FORWARD, CONTINUOUS_MAX_REVERSE, CONTINUOUS_MAX_FORWARD));
		Servos[3].write(map(packet.data[1], RED_MAX_REVERSE, RED_MAX_FORWARD, CONTINUOUS_MAX_REVERSE, CONTINUOUS_MAX_FORWARD));
        Serial.println("IN2");
        break;
      }

      case RC_SHIMBLEBOARD_SERVOABSOLUTE_DATAID: //Servo Absolute
      {
        for (int i = 0; i < RC_SHIMBLEBOARD_SERVOABSOLUTE_DATACOUNT; i++)
        {
           //Servos[i].write(packet.data[i]);
        }
        break;    
      }

      case RC_SHIMBLEBOARD_MAINGIMBALABS_DATAID: //Main Gimbal Abolute
      {
        for (int i = 0; i < RC_SHIMBLEBOARD_MAINGIMBALABS_DATACOUNT; i++)
        {
           //Servos[i].write(packet.data[i]);
        }
        break;    
      }

      case RC_SHIMBLEBOARD_DRIVEGIMBALABS_DATAID: //Drive Gimbal Abolute
      {
        for (int i = 0; i < RC_SHIMBLEBOARD_DRIVEGIMBALABS_DATACOUNT; i++)
        {
           //Servos[i].write(packet.data[i]);
        }
        break;    
      }

      /*case RC_SHIMBLEBOARD_SERVOTOSETPOS_DATAID: //Servo to set position
      {
        for (int i = 0; i < RC_SHIMBLEBOARD_SERVOTOSETPOS_DATACOUNT; i++)
        {
           Servos[i].write( enum value? );
        }
        break; 
      } */
    }
  }
  		

  /*
  if (millis() - telemetry_time >= 1000) // If it's been more than 1 second since telemetry was sent,
  {                                      // send telemetry and update telemetry_time
    telemetry_time = millis();
    RoveComm->write(RC_SHIMBLEBOARD_SERVOPOS_DATAID, RC_SHIMBLEBOARD_SERVOPOS_DATACOUNT, servo_positions);
    delay(ROVECOMM_DELAY);
  }
  */
}
