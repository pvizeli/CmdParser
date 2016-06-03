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
    // Get command (first argument) in upper case back -> getCommand()
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
