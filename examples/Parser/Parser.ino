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

char myTestCmd[] = "START \"Hallo world\" sensor";

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
    // cmdParser.setOptKeyValue(false); // default

    if (cmdParser.parseCmd(myTestCmd) != CMDPARSER_ERROR) {
        Serial.print("Command: ");
        Serial.println(cmdParser.getCommand());

        Serial.print("Size of parameter: ");
        Serial.println(cmdParser.getParamCount());

        Serial.print("Param 1: ");
        Serial.println(cmdParser.getCmdParam(1));

        // check param 2 from SRAM
        if (cmdParser.equalCmdParam(2, "senSor")) {
            Serial.println("Found Sensor in with SRAM");
        }

        // check param 2 from PROGMEM
        if (cmdParser.equalCmdParam_P(2, PSTR("senSor"))) {
            Serial.println("Found Sensor in with PROGMEM");
        }
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
            for (size_t i = 0; i < count; i++) {

                Serial.print("Param ");
                Serial.print(i);
                Serial.print(": ");
                Serial.println(cmdParser.getCmdParam(i));
            }

            // Check end
            if (cmdParser.equalCommand_P(PSTR("Quit"))) {
                Serial.println("You have write a QUIT Command!");
            }

        } else {
            Serial.println("Parser error!");
        }

    } else {
        Serial.println("TIMEOUT!");
    }
}
