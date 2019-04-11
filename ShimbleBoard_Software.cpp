// Shimble Board ///////////////////////////////////////////////////////////////////////////////////////
    // Main .cpp File
//
// Created for 2019 Valkyrie by: Andrew Phillips, ajpnq2
//
// Libraries ///////////////////////////////////////////////////////////////////////////////////////////
#include "ShimbleBoard_Software.h"
#include "RoveComm.h"
#include <Energia.h>

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

  Servos[5].write(89);
  Servos[1].write(150);
  Servos[2].write(75);
  Servos[3].write(15);


  Serial.println("Shimble Setup Complete.");
}

void shimbleLoop(rovecomm_packet packet, RoveCommEthernetUdp * RoveComm) //void loop
{ 
  RC_SHIMBLEBOARD_SERVOPOS_DATATYPE servo_positions[RC_SHIMBLEBOARD_SERVOPOS_DATACOUNT];

  for (int i = 0; i < RC_SHIMBLEBOARD_SERVOPOS_DATACOUNT; i++)
  {
    servo_positions[i] = Servos[i].read();
  }

  if(packet.data_id != 0)
  {
    switch (packet.data_id)
    {
      case RC_SHIMBLEBOARD_SERVOINC_DATAID: //Servo Increment
      {
		for (int i = 0; i < RC_SHIMBLEBOARD_SERVOINC_DATACOUNT; i++)
        {
		   
		   Servos[i].write(servo_positions[i] + packet.data[i]);
        }
        break;
      }

      case RC_SHIMBLEBOARD_MAINGIMBALINC_DATAID: //Main Gimbal Increment
      {
        int new_pos[2];
		   
		new_pos[1] = servo_positions[1] + packet.data[1];
	    
		// Check new values against servo range
		if (new_pos[1] > 45) new_pos[1] = 45;
		else if (new_pos[1] < 0) new_pos[1] = 0;
		
		for (int i = 0; i < RC_SHIMBLEBOARD_MAINGIMBALINC_DATACOUNT; i++)
        {  
		   Servos[1].write(new_pos[1]);
        }
        break;
      }

      case RC_SHIMBLEBOARD_DRIVEGIMBALINC_DATAID: //Drive Gimbal Increment
      {
	    int new_pos[2];
		
		new_pos[0] = servo_positions[2] + packet.data[0];
		new_pos[1] = servo_positions[3] + packet.data[1];
	    
		// Check new values against servo range
		//if (new_pos[0] > 180) new_pos[0] = 180;
		//else if (new_pos[0] < 120) new_pos[0] = 120;
		if (new_pos[1] > 45) new_pos[1] = 45;
		else if (new_pos[1] < 0) new_pos[1] = 0;
		
		
        for (int i = 0; i < RC_SHIMBLEBOARD_DRIVEGIMBALINC_DATACOUNT; i++)
        {
		   Servos[i + 2].write(new_pos[i]);
        }
        break;
      }

      case RC_SHIMBLEBOARD_SERVOABSOLUTE_DATAID: //Servo Absolute
      {
        for (int i = 0; i < RC_SHIMBLEBOARD_SERVOABSOLUTE_DATACOUNT; i++)
        {
           map(packet.data[i], -100, 100, 0, 180);
		   Servos[i].write(packet.data[i]);
        }
        break;    
      }

      case RC_SHIMBLEBOARD_MAINGIMBALABS_DATAID: //Main Gimbal Abolute
      {
        int mapped_pos[2];
		
		mapped_pos[0] = map(packet.data[0], -100, 100, 85, 94); // Continuous servo map
		mapped_pos[1] = map(packet.data[4], -100, 100, 120, 180); // Rest state: 150
		
		if (mapped_pos[0] < 92 && mapped_pos[0] > 87)
		{
			mapped_pos[0] = 89;
		}
		
		Servos[0].write(mapped_pos[0]);
		Servos[1].write(mapped_pos[1]);
		
		for (int i = 0; i < RC_SHIMBLEBOARD_MAINGIMBALABS_DATACOUNT; i++)
        {  
		//   Servos[i].write(mapped_pos[i]);
        }
        break;    
      }

      case RC_SHIMBLEBOARD_DRIVEGIMBALABS_DATAID: //Drive Gimbal Abolute
      {
        int mapped_pos[2];
		
		//mapped_pos[0] = map(packet.data[0], -100, 100, 0, 40); // 
		mapped_pos[1] = map(packet.data[1], -100, 100, 0, 45); // Rest state: 15
		
		for (int i = 0; i < RC_SHIMBLEBOARD_DRIVEGIMBALABS_DATACOUNT; i++)
        {
		   Servos[i + 2].write(mapped_pos[i]);
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

  if (millis() - telemetry_time >= 1000) // If it's been more than 1 second since telemetry was sent,
  {                                      // send telemetry and update telemetry_time
    telemetry_time = millis();
    RoveComm->write(RC_SHIMBLEBOARD_SERVOPOS_DATAID, RC_SHIMBLEBOARD_SERVOPOS_DATACOUNT, servo_positions);
    delay(ROVECOMM_DELAY);
  }
}
