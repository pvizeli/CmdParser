/* Copyright 2016 Pascal Vizeli <pvizeli@syshack.ch>
 * BSD License
 *
 * https://github.com/pvizeli/CmdParser
 */

////
// This example is a demo for CmdCallback with PROGMEM.
// It parse a command line and process callback function.
// This exemple is without Key Value parser function
////

#include <CmdBuffer.hpp>
#include <CmdCallback.hpp>
#include <CmdParser.hpp>

CmdCallback_P<3> cmdCallback;

void setup()
{
    Serial.begin(115200);

    cmdCallback.addCmd(PSTR("HALLO"), &functHallo);
    cmdCallback.addCmd(PSTR("QUIT"), &functQuit);
    cmdCallback.addCmd(PSTR("SET"), &functSet);
}

void loop()
{
    CmdBuffer<32> myBuffer;
    CmdParser     myParser;

    // Set parser options
    //...

    Serial.println("Type you commands. Supported: ");
    Serial.println("1: hallo");
    Serial.println("2: set alarm on/off");
    Serial.println("3: quit");

    // Auto Handling
    cmdCallback.loopCmdProcessing(&myParser, &myBuffer, &Serial);

    // also possible manual with
    // cmdCallback.processCmd(myParser);
}

void functHallo(CmdParser *myParser) { Serial.println("Receive Hallo"); }

void functSet(CmdParser *myParser)
{
    Serial.println("Receive Set");

    // Alarm
    if (myParser->equalCmdParam_P(1, PSTR("ALARM"))) {
        Serial.println(myParser->getCmdParam(2));
    }
    // Command Unknwon
    else {
        Serial.println("Only Alarm is allowed!");
    }
}

void functQuit(CmdParser *myParser) { Serial.println("Receive Quit"); }
