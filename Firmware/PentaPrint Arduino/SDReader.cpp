/**
 * Author: Shifan Liu
 */
#include "SDReader.h"

// Constructor
SDReader::SDReader(GcodeParser& parser, long* targetPositions)
    : parser(parser), targetPositions(targetPositions) {}

// Initializes the SD card
bool SDReader::initialize() {
  delay(100);
  if (!SD.begin(chipSelect)) {
    return false;
  }
  return true;
}

// Reads and executes a G-code file line-by-line
bool SDReader::readAndExecuteGcode(const char* filename) {
  File gcodeFile = SD.open(filename);

  if (!gcodeFile) {
      return false;
  }

  // Read and execute each line
  while (gcodeFile.available()) {
    String gcodeLine = gcodeFile.readStringUntil('\n');
    gcodeLine.trim();  // Remove any trailing whitespace

    if (gcodeLine.length() > 0) {
      // Zero all values
      for (int i = 0; i < 6; i++) {
        targetPositions[i] = 0;  // Set each position to 0
      }
      parser.parseGcode(gcodeLine, targetPositions);  // Parse the G-code line
      steppers.moveTo(targetPositions);
      steppers.runSpeedToPosition();  // Block until all motors reach their target positions
    }
  }

  // Close the file after executing all lines
  gcodeFile.close();
  return true;
}
