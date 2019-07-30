/* Copyright 2016 Pascal Vizeli <pvizeli@syshack.ch>
 * Copyright 2019 Matthias Homann
 * BSD License
 *
 * https://github.com/pvizeli/CmdParser
 */

////
// This example is a demo for non-blocking CmdCallback.
// It regularly checks for new characters on the serial interface
// and parses the read string if the 'endchar' (\n) was entered.
////

#include <CmdBuffer.hpp>
#include <CmdCallback.hpp>
#include <CmdParser.hpp>

CmdCallback<3> cmdCallback;

CmdBuffer<32> myBuffer;
CmdParser     myParser;

char strHallo[] = "HALLO";
char strQuit[]  = "QUIT";
char strSet[]   = "SET";

void functHallo(CmdParser *myParser) { Serial.println("Receive Hallo"); }

void functSet(CmdParser *myParser)
{
    Serial.println("Receive Set");

    // Alarm
    if (myParser->equalCmdParam(1, "ALARM")) {
        Serial.println(myParser->getCmdParam(2));
    }
    // Command Unknwon
    else {
        Serial.println("Only Alarm is allowed!");
    }
}

void functQuit(CmdParser *myParser) { Serial.println("Receive Quit"); }

void setup()
{
    Serial.begin(115200);

    cmdCallback.addCmd(strHallo, &functHallo);
    cmdCallback.addCmd(strQuit, &functQuit);
    cmdCallback.addCmd(strSet, &functSet);

    // Set parser options:
    // enable local echo
    myBuffer.setEcho(true);
    // ...

    Serial.println("Type you commands. Supported: ");
    Serial.println("1: hallo");
    Serial.println("2: set alarm on/off");
    Serial.println("3: quit");
}

void loop()
{

    // Check for new char on serial and call function if command was entered
    cmdCallback.updateCmdProcessing(&myParser, &myBuffer, &Serial);

    // do some other stuff...
    delay(100);
}
