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
#define ROVECOMM_DELAY    5
    
// Variable Declarations ////////////////////////////////////////////////////////////////////////////////
Servo Servos[8];
uint16_t servo_positions[8];
uint32_t telemetry_time = 0;

// Function Declarations ////////////////////////////////////////////////////////////////////////////////
void shimbleSetup();
void shimbleLoop(rovecomm_packet packet);

#endif