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
#define ROVECOMM_DELAY        5

	//Misc Values
#define IGNORE_THRESHOLD      5
#define INC_VALUE             3

#deine

	//Servo Positions
#define SERVO_1_REST         89
#define SERVO_2_REST        150
#define SERVO_3_REST        126
#define SERVO_4_REST         90

#define SERVO_1_MAX          92
#define SERVO_2_MAX         180
#define SERVO_3_MAX         162
#define SERVO_4_MAX         180

#define SERVO_1_MIN          85
#define SERVO_2_MIN          64
#define SERVO_3_MIN          90
#define SERVO_4_MIN           0

// Function Declarations ////////////////////////////////////////////////////////////////////////////////
void shimbleSetup();
void shimbleLoop(rovecomm_packet packet, RoveCommEthernetUdp * RoveComm);

#endif