/**
 * Author: Shifan Liu
 */
#ifndef SDREADER_H
#define SDREADER_H

#include <SD.h>
#include "GcodeParser.h"

// SDReader class to handle SD card file reading and G-code execution
class SDReader {
public:
    // Constructor
    SDReader(GcodeParser& parser, long* targetPositions);

    // Initializes the SD card
    bool initialize();

    // Reads and executes a G-code file line-by-line
    bool readAndExecuteGcode(const char* filename);

    // SD card chip select pin
    static const int chipSelect = 10;

private:
    int chipSelectPin;
    GcodeParser& parser;
    long* targetPositions;
};

#endif // SDREADER_H
