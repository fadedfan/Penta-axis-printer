/**
 * Author: Shifan Liu
 */
#ifndef STEPPER_CONFIG_H
#define STEPPER_CONFIG_H

#include <AccelStepper.h>
#include <MultiStepper.h>

// Pin definitions for motors
#define dirPin_x 31
#define stepPin_x 30
#define dirPin_y 33
#define stepPin_y 32
#define dirPin_z 35
#define stepPin_z 34
#define dirPin_yaw 37
#define stepPin_yaw 36
#define dirPin_pitch 39
#define stepPin_pitch 38
#define dirPin_ex 41
#define stepPin_ex 40

// Stepper settings
#define microstep 16

// Declare stepper instances as extern
extern AccelStepper stepperX;
extern AccelStepper stepperY;
extern AccelStepper stepperZ;
extern AccelStepper stepperYaw;
extern AccelStepper stepperPitch;
extern AccelStepper stepperEx;

// Declare MultiStepper instance as extern
extern MultiStepper steppers;

// Declare steps per mm as extern
extern const float stepsPerMmXY;
extern const float stepsPerMmZ;
extern const float stepsPerMmE;
extern const float stepsPerDeg;

// Function to initialize stepper settings
void setupSteppers();

#endif // STEPPER_CONFIG_H
