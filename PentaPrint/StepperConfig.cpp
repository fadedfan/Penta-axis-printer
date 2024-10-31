/**
 * Author: Shifan Liu
 */
#include "StepperConfig.h"

// Define stepper instances
AccelStepper stepperX(AccelStepper::DRIVER, stepPin_x, dirPin_x);
AccelStepper stepperY(AccelStepper::DRIVER, stepPin_y, dirPin_y);
AccelStepper stepperZ(AccelStepper::DRIVER, stepPin_z, dirPin_z);
AccelStepper stepperYaw(AccelStepper::DRIVER, stepPin_yaw, dirPin_yaw);
AccelStepper stepperPitch(AccelStepper::DRIVER, stepPin_pitch, dirPin_pitch);
AccelStepper stepperEx(AccelStepper::DRIVER, stepPin_ex, dirPin_ex);

// Define MultiStepper instance
MultiStepper steppers;

// Define steps per mm parameters
const float stepsPerMmXY = - 200.0 / 32 * microstep; // X and Y axes
const float stepsPerMmZ = - 200.0 / 8 * microstep;   // Z axis
const float stepsPerMmE = 200.0 / 160 * microstep; // Extruder
const float stepsPerDeg = 200.0 / 360 * microstep;  // for yaw/pitch

// Function to initialize stepper settings
void setupSteppers() {
    // Set maximum speed for each stepper (default)
    stepperX.setMaxSpeed(8000);
    stepperY.setMaxSpeed(8000);
    stepperZ.setMaxSpeed(8000);
    stepperYaw.setMaxSpeed(2000);
    stepperPitch.setMaxSpeed(2000);
    stepperEx.setMaxSpeed(2000);

    // Add steppers to the MultiStepper object
    steppers.addStepper(stepperX);
    steppers.addStepper(stepperY);
    steppers.addStepper(stepperZ);
    steppers.addStepper(stepperYaw);
    steppers.addStepper(stepperPitch);
    steppers.addStepper(stepperEx);
}
