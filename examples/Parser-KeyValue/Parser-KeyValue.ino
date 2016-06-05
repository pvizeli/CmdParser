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

char myTestCmd[] = "run sensor=\"Set my val\" valve=off alarm=yes";

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
    cmdParser.setOptKeyValue(true);

    if (cmdParser.parseCmd(myTestCmd) != CMDPARSER_ERROR) {
        Serial.print("Command: ");
        Serial.println(cmdParser.getCommand());

        Serial.print("Size of parameter: ");
        Serial.println(cmdParser.getParamCount());

        // if command RUN
        if (cmdParser.equalCommand_P(PSTR("RUN"))) {

            Serial.print("Sensor: ");
            Serial.println(cmdParser.getValueFromKey_P(PSTR("SENSOR")));

            Serial.print("Alarm: ");
            Serial.println(cmdParser.getValueFromKey_P(PSTR("ALARM")));

            Serial.print("Valve: ");
            Serial.println(cmdParser.getValueFromKey_P(PSTR("VALVE")));
        } else {
            Serial.println("Command is not run!");
        }
    }
}

void loop()
{

    // alarm an
    if (cmdParser.equalValueFromKey_P(PSTR("ALARM"), PSTR("YES"))) {
        Serial.println("Alarm on");

    } else {
        Serial.println("Alarm off");
    }

    delay(30000);
}
