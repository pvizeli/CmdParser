/* Copyright 2016 Pascal Vizeli <pvizeli@syshack.ch>
 * BSD License
 *
 * https://github.com/pvizeli/CmdParser
 */

////
// This example is a demo for CmdBuffer.
// It will read printable data from serial into modern buffer
////

#include <CmdBuffer.hpp>

// Create a buffer with size of 64 characters
CmdBuffer<64> cmdBuffer;

void setup()
{
    Serial.begin(115200);

    ////
    // possible to change read line option from buffer
    // cmdBuffer.setEndChar('\n'); // default
}

void loop()
{
    Serial.println("Start Reading");

    // Read line from Serial until timeout
    if (cmdBuffer.readFromSerial(&Serial, 30000)) {
        Serial.println("Line have readed:");
        Serial.println(cmdBuffer.getStringFromBuffer());
    } else {
        Serial.println("TIMEOUT!");
    }
}
