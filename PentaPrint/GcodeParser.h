/**
 * Author: Shifan Liu
 */

#ifndef GCODE_PARSER_H
#define GCODE_PARSER_H

#include "StepperConfig.h" // Include the stepper config

class GcodeParser {
public:
    GcodeParser();
    void parseGcode(String gcode, long* targetPositions); // Add targetPositions as parameter

private:
    float extractValue(String gcode, char axis);
};

#endif // GCODE_PARSER_H

