/* Copyright 2016 Pascal Vizeli <pvizeli@syshack.ch>
 * BSD License
 *
 * https://github.com/pvizeli/CmdParser
 */

////
// This example is a demo for CmdParser.
// It parse a command line from string buffer or CmdBuffer.
////

#include <CmdParser.hpp>

CmdParser cmdParser;

char myTestCmd[] = "START sensor1 \"Hallo world\"";

void setup()
{
    Serial.begin(115200);

    ////
    // Enable cmd strings with "" -> SET VAL "HALLO WORLD"
    // cmdParser.setOptIgnoreQuote(false) // default

    ////
    // Set command seperator.
    // cmdParser.setOptSeperator(' '); // default

    ////
    // Use Key=Value with getValueFromKey/_P() by parser
    // cmdParser.setOptCmdUpper(true); // default

    if (cmdParser.parseCmd(myTestCmd)) {
        Serial.print("Command: ");
        Serial.println(cmdParser.getCommand());

        Serial.print("Size of parameter: ");
        Serial.println(cmdParser.getParamCount());

        Serial.print("Param 1: ");
        Serial.println(cmdParser.getCmdParam(1));

        Serial.print("Param 2 (upper case): ");
        Serial.println(cmdParser.getCmdParamUpper(2));
    }
}

void loop()
{
    // use own buffer from serial input
    CmdBuffer<32> myBuffer;

    Serial.println("Start Reading");

    // Read line from Serial until timeout
    if (myBuffer.readFromSerial(&Serial, 30000)) {

        if (cmdParser.parseCmd(&myBuffer) != CMDPARSER_ERROR) {
            Serial.print("Line have readed: ");
            Serial.println(myBuffer.getStringFromBuffer());

            Serial.print("Command: ");
            Serial.println(cmdParser.getCommand());

            Serial.print("Size of parameter: ");
            Serial.println(cmdParser.getParamCount());

            const size_t count = cmdParser.getParamCount();
            for (size_t i = 0; i <= count; i++) {

                Serial.print("Param ");
                Serial.print(i);
                Serial.print(": ");
                Serial.println(cmdParser.getCmdParam(i));
            }

        } else {
            Serial.println("Parser error!");
        }

    } else {
        Serial.println("TIMEOUT!");
    }
}
