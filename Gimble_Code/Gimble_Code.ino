#include <Energia.h>
#include <Servo.h>
#include "RoveComm.h"
#include "Gimble_Code.h"

Servo servos[8];
int16_t servoPosition[8]; 
//uint16_t servoOrigin[8];
uint16_t servoMax[8];
uint16_t servoMin[8];

RoveCommEthernet  RoveComm;
rovecomm_packet packet;

void setup()
{
	Serial.begin(115200);
	
	delay(ROVECOMM_DELAY);
	RoveComm.begin(RC_DRIVEBOARD_FOURTHOCTET, &TCPServer);
	delay(ROVECOMM_DELAY);

	// attaches the servo array to the respective pins (1-8 servos are 0-7)
	servos[0].attach(SERVO1);
	servos[1].attach(SERVO2);
	servos[2].attach(SERVO3);
	servos[3].attach(SERVO4);
	servos[4].attach(SERVO5);
	servos[5].attach(SERVO6);
	servos[6].attach(SERVO7);
	servos[7].attach(SERVO8);

	// servo positions are set to starting positions
	servoPosition[0] = SERVO1_START;
	servoPosition[1] = SERVO2_START;
	servoPosition[2] = SERVO3_START;
	servoPosition[3] = SERVO4_START;
	servoPosition[4] = SERVO5_START;
	servoPosition[5] = SERVO6_START;
	servoPosition[6] = SERVO7_START;
	servoPosition[7] = SERVO8_START;

	// servo max values put in an array
	servoMax[0] = SERVO1_MAX;
	servoMax[1] = SERVO2_MAX;
	servoMax[2] = SERVO3_MAX;
	servoMax[3] = SERVO4_MAX;
	servoMax[4] = SERVO5_MAX;
	servoMax[5] = SERVO6_MAX;
	servoMax[6] = SERVO7_MAX;
	servoMax[7] = SERVO8_MAX;

	// servo min values put in an array
	servoMin[0] = SERVO1_MIN;
	servoMin[1] = SERVO2_MIN;
	servoMin[2] = SERVO3_MIN;
	servoMin[3] = SERVO4_MIN;
	servoMin[4] = SERVO5_MIN;
	servoMin[5] = SERVO6_MIN;
	servoMin[6] = SERVO7_MIN;
	servoMin[7] = SERVO8_MIN;

	startupRoutine();

	Serial.println("Gimble Setup Complete");
}

void loop()
{
    //  rovecomm_packet packet;
    packet = RoveComm.read();

    if(packet.data_id != 0)
    {
        switch(packet.data_id)
        {
            case RC_SHIMBLEBOARD_LEFT_DRIVE_SERVOINC_DATAID:
            {
                Serial.println("Left Drive:");
                dataOutput();
                gimbalIncrement(0, 2);
                break;
            }
            
            case RC_SHIMBLEBOARD_RIGHT_DRIVE_SERVOINC_DATAID:
            {
                Serial.println("Right Drive:");
                dataOutput();
                gimbalIncrement(2, 4);
                break;
            }
            
            case RC_SHIMBLEBOARD_LEFT_MAIN_SERVOINC_DATAID:
            {
                Serial.println("Left Main:");
                dataOutput();
                gimbalIncrement(4, 6);
                break;
            }
            
            case RC_SHIMBLEBOARD_RIGHT_MAIN_SERVOINC_DATAID:
            {
                Serial.println("Right Main:");
                dataOutput();
                gimbalIncrement(6, 8);
                break;
            }
        }
    }
}

void startupRoutine()
{
    delay(STARTUP_DELAY);
    for(int i = 0; i < 8; i++)
    {
    	servos[i].write(servoMin[i]);
    }
    delay(STARTUP_DELAY);
    for(int i = 0; i < 8; i++)
    {
    	servos[i].write(servoMax[i]);
    }
    delay(STARTUP_DELAY);
    for(int i = 0; i < 8; i++)
    {
    	servos[i].write(servoPosition[i]);
    }
    Serial.println("Startup Routine Complete");
}

void dataOutput()
{
	for(int i = 0; i < 2; i++)
	{
		Serial.println(packet.data[i]);
	}
}

void gimbalIncrement(const int & servoNum1, const int & servoNum2)
{
    int16_t *incrementValues = (int16_t*)packet.data;

    Serial.println("Increments");
    Serial.println(incrementValues[0]);
    Serial.println(incrementValues[1]);

    
    for(int i = servoNum1; i < servoNum2; i++)
    {
        if(incrementValues[i - servoNum1] > IGNORE_THRESHOLD)
        {
            servoPosition[i] += incrementValues[i - servoNum1];
            
            if(servoPosition[i] >= servoMax[i])
            {
                servoPosition[i] = servoMax[i];
            }
        }
        
        if(incrementValues[i - servoNum1] < -IGNORE_THRESHOLD)
        {
            servoPosition[i] += incrementValues[i - servoNum1];
            
            if(servoPosition[i] <= servoMin[i])
            {
                servoPosition[i] = servoMin[i]; 
            }
            Serial.println(servoPosition[i]);
        }
        
        Serial.println(servoPosition[i]);
        servos[i].write((int)servoPosition[i]);
        Serial.println(servos[i].read());
    }
}
