[![Build Status](https://dev.azure.com/pascalvizeli/CmdParser/_apis/build/status/CI?branchName=master)](https://dev.azure.com/pascalvizeli/CmdParser/_build/latest?definitionId=3&branchName=master)

# CmdParser

A simple and most powerful cmd parser with small memory footprint and realy
fast algorithm.

This library is for handling commands over i.e. serial and short data transfers.
If you need transfer complex data, use JSON. You can combine this 2 technics.
Use this library for starting progress and for asking sensor data from sending
with JSON.

All function with "static" characters possible handling with PROGMEM if you
add ```_P``` to the functions end for CmdParser and CmdCallback object.

For handling show all examples.

## Parser Object

The function ```parseCmd``` will change the buffer! Only the parser object can
handle the new buffer...

Default it use a static parameter list. With KeyValue option you can change
to dynamic key=value parser handling.

```c++
#include <CmdParser.hpp>

CmdParser myParser;

myParser.parseCmd(myBuffer); // CmdBuffer Object
myParser.parseCmd(byteBuffer, size); // Binary buffer
myParser.parseCmd(cString); // C string buffer

```

### Options

- ```setOptIgnoreQuote``` (default off) support string with "my value"
- ```setOptSeperator``` (default ' ') use this character for seperate cmd
- ```setOptKeyValue``` (default off) Support dynamic key=value feature

## Buffer Object

```c++
#include <CmdBuffer.hpp>

CmdBuffer<32> myBuffer;

// Reading Data
myBuffer.readFromSerial(&Serial, numTimeout);

// Read single character
myBuffer.readSerialChar(&Serial);
```

### Options

- ```setEndChar``` (default '\n') set character for stop reading. Normal is a line end.
- `setBackChar` (default '\h') set the character for backspace.
- `setEcho` (default 'false') enable local echo.

## Callback Object

```c++
#include <CmdCallback.hpp>

CmdCallback<5> myCallback; // Object for handling 5 function in SRAM
CmdCallback_P<5> myCallbackP; // Object for handling 5 function in PROGMEM

// add function
myCallbackP.addCmd(PSTR("SET"), &myFunctForSet);

// Automatic proccessing
myCallbackP.loopCmdProcessing(&myParser, &myBuffer, &Serial);

// Manual
myCallbackP.processCmd(cstrCmd);

// Check for new chars and check if complete command was entered
// This function is non-blocking to be used in a loop.
myCallbackP.updateCmdProcessing(&myParser, &myBuffer, &Serial);

// Search command in the buffer, returns true if such command was defined.
myCallbackP.hasCmd(cstrCmd);

```
