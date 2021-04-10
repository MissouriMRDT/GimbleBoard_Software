#ifndef Gimble_Code_h
#define Gimble_Code_h

#include <Energia.h>
#include <Servo.h>
#include "RoveComm.h"

//Constants

  //Pins
#define SERVO1 PF_1
#define SERVO2 PF_2
#define SERVO3 PF_3
#define SERVO4 PG_0
#define SERVO5 PG_1
#define SERVO6 PK_4
#define SERVO7 PK_5
#define SERVO8 PM_0

  //Starting
#define SERVO1_START 135
#define SERVO2_START 135
#define SERVO3_START 135
#define SERVO4_START 135
#define SERVO5_START 135
#define SERVO6_START 135
#define SERVO7_START 135
#define SERVO8_START 135
  //Max
#define SERVO1_MAX 180
#define SERVO2_MAX 180
#define SERVO3_MAX 180
#define SERVO4_MAX 180
#define SERVO5_MAX 180
#define SERVO6_MAX 180
#define SERVO7_MAX 180
#define SERVO8_MAX 180
  //Min
#define SERVO1_MIN 0
#define SERVO2_MIN 0
#define SERVO3_MIN 0
#define SERVO4_MIN 0
#define SERVO5_MIN 0
#define SERVO6_MIN 0
#define SERVO7_MIN 0
#define SERVO8_MIN 0

  //Delays
#define ROVECOMM_DELAY 10
#define STARTUP_DELAY 2000
/*#define SERVO_START 1
#define SERVO_MAX 2500
#define SERVO_MIN 500*/

#define IGNORE_THRESHOLD 2

//Functions
void startupRoutine();
void dataOutput();
void gimbalIncrement(const int & servoNum1, const int & servoNum2);
void gimbalAbsolute(const int & servoNum1, const int & servoNum2);

#endif
