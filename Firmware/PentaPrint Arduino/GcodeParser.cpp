/**
 * Author: Shifan Liu
 */

#include "GcodeParser.h"

// Constructor
GcodeParser::GcodeParser() {}

// Method to parse G-code
void GcodeParser::parseGcode(String gcode, long* targetPositions) {
    // Remove comments
    int commentIndex = gcode.indexOf(';');
    if (commentIndex != -1) {
        gcode = gcode.substring(0, commentIndex);
    }
    
    gcode.trim();  // Remove leading and trailing whitespace

    if (gcode.startsWith("G1")) {  // Handle G1 command
        float x = NAN, y = NAN, z = NAN, a = NAN, b = NAN, e = NAN, f = NAN;

        // Extract parameters
        int xIndex = gcode.indexOf('X');
        int yIndex = gcode.indexOf('Y');
        int zIndex = gcode.indexOf('Z');
        int aIndex = gcode.indexOf('A');
        int bIndex = gcode.indexOf('B');
        int eIndex = gcode.indexOf('E');
        int fIndex = gcode.indexOf('F');

        if (xIndex != -1) x = extractValue(gcode, 'X');
        if (yIndex != -1) y = extractValue(gcode, 'Y');
        if (zIndex != -1) z = extractValue(gcode, 'Z');
        if (aIndex != -1) a = extractValue(gcode, 'A');
        if (bIndex != -1) b = extractValue(gcode, 'B');
        if (eIndex != -1) e = extractValue(gcode, 'E');
        if (fIndex != -1) f = extractValue(gcode, 'F');

        // Convert G-code positions to target positions in steps
        targetPositions[0] = !isnan(x) ? (x * stepsPerMmXY) : stepperX.currentPosition(); // X
        targetPositions[1] = !isnan(y) ? (y * stepsPerMmXY) : stepperY.currentPosition(); // Y
        targetPositions[2] = !isnan(z) ? (z * stepsPerMmZ) : stepperZ.currentPosition();  // Z
        targetPositions[3] = !isnan(a) ? (a * stepsPerDeg) : stepperYaw.currentPosition(); // Yaw
        targetPositions[4] = !isnan(b) ? (b * stepsPerDeg) : stepperPitch.currentPosition(); // Pitch
        targetPositions[5] = !isnan(e) ? (e * stepsPerMmE) : stepperEx.currentPosition(); // Extruder

        // Set maximum speed based on feedrate if provided
        if (!isnan(f)) {
          stepperX.setMaxSpeed(f);
          stepperY.setMaxSpeed(f);
          stepperZ.setMaxSpeed(f >= 16000 ? 16000 : f); // Cap Z speed
          stepperYaw.setMaxSpeed(f);
          stepperPitch.setMaxSpeed(f);
          stepperEx.setMaxSpeed(f);
        }
    }
}

// Method to extract numeric values from G-code
float GcodeParser::extractValue(String gcode, char axis) {
    int index = gcode.indexOf(axis);
    int nextSpace = gcode.indexOf(' ', index + 1);
    if (nextSpace == -1) {
        return gcode.substring(index + 1).toFloat();
    } else {
        return gcode.substring(index + 1, nextSpace).toFloat();
    }
}
