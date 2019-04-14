// Shimble Board ////////////////////////////////////////////////////////////////////////////////////////
    // Header File
//
// Created for 2019 Valkyrie by: Andrew Phillips, ajpnq2
//
// Libraries /////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ShimbleBoard
#define _ShimbleBoard

#include "RoveComm.h"
#include "Servo.h"

// Constants /////////////////////////////////////////////////////////////////////////////////////////////
    // Pinout
#define SERVO_1_CRTL_PIN   PM_7
#define SERVO_2_CRTL_PIN   PA_7
#define SERVO_3_CRTL_PIN   PM_6
#define SERVO_4_CRTL_PIN   PM_1
#define SERVO_5_CRTL_PIN   PM_0
#define SERVO_6_CRTL_PIN   PK_5
#define SERVO_7_CRTL_PIN   PK_4
#define SERVO_8_CRTL_PIN   PG_1
    //Delays
#define ROVECOMM_DELAY     5

	//Misc Values
#define IGNORE_THRESHOLD   50
#define INC_VALUE          35

	//Servo Positions
#define SERVO_1_REST       1472 //1470 is boundary in which it stops drifting to right; 1476 is boundary in which it stops drifting left; 1473 is middle, no drifting
#define SERVO_2_REST       1400 //Main cam pitch facing up. Can lower value to face further upwards.
#define SERVO_3_REST       1830 //Drive cam pan facing forward.
#define SERVO_4_REST       1500 //Drive cam pitch facing forward.

#define SERVO_1_MAX        1523 //Change value to change how fast the pan moves left and right. 
#define SERVO_2_MAX        2000 //Main cam pitch facing down; Higher than 2000 faces camera directly into 3d print.
#define SERVO_3_MAX        1400 //Drive cam pan max right; Lower than 1400 causes servo to jitter.
#define SERVO_4_MAX        2200 //Drive cam pitch facing down; Higher than 2200 causes servo to jitter.

#define SERVO_1_MIN        1423 //Change value to change how fast the pan moves left and right.
#define SERVO_2_MIN        1000
#define SERVO_3_MIN        2230 //Drive cam pan max left; Higher than 2230 causes servo to jitter.
#define SERVO_4_MIN        750 //Drive cam pitch facing up; Lower than 750 causes servo to jitter.

// Function Declarations ////////////////////////////////////////////////////////////////////////////////
void shimbleSetup();
void shimbleLoop(rovecomm_packet packet, RoveCommEthernetUdp * RoveComm);

#endif