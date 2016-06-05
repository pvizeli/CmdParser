# CmdParser
A simple and most powerfull cmd parser with small memory footprint.

This library is for handling commands over i.e. serial and short data transfers.
If you need transfer complex data, use JSON. You can combine this 2 technics.
Use this library for starting progress and for asking sensor data from sending
with JSON.

For handling show all examples.

## Parser Object

The function ```parseCmd``` will change the buffer! Only the parser object can
handle the new buffer...

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

myBuffer.readFromSerial(&Serial, numTimeout);
```

### Options
- ```setEndChar``` (default '\n') set character for stop reading. Normal is a line end.
