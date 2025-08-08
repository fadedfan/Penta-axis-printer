#include "StepperConfig.h"
#include "GcodeParser.h"
#include "SDReader.h"

// GcodeParser instance
GcodeParser gcodeParser;
long targetPositions[6];      // Array to store target positions for each motor

// SDReader instance
SDReader sdReader(gcodeParser, targetPositions);

//Helper for clear
void clearPositions() {
  for (int i = 0; i < 6; i++) {
    targetPositions[i] = 0;  // Set each position to 0
  }
}

void setup() {
  Serial.begin(115200);  
  while (!Serial) ;
  Serial.println("Enter filename or gcode commands!");
  
  // Initialize SD card
  if (!sdReader.initialize()) {
    Serial.println("SD card initialization failed!");
    while(1);
  }
  Serial.println("SD card initialized.");

  setupSteppers(); 
}

void loop() {
  // Check if there's input from the Serial Monitor
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // Read the entire line until newline
    input.trim();

    // Check the input
    if (input.startsWith("G")) {
      // Zero all values
      clearPositions();
      gcodeParser.parseGcode(input, targetPositions);  // Parse the G-code line
      steppers.moveTo(targetPositions);
      steppers.runSpeedToPosition();  // Block until all motors reach their target positions
    } else {
      if (!sdReader.readAndExecuteGcode(input.c_str())) {
        Serial.println("Error opening!");
      } else {
        Serial.println("Finished executing G-code commands.");
      }
    } 
  }
}
