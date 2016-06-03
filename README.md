# CmdParser
A simple and most powerfull cmd parser with small memory footprint.

This library is for handling commands over i.e. serial and short data transfers.
If you need transfer complex data, use JSON. You can combine this 2 technics.
Use this library for starting progress and for asking sensor data from sending
with JSON.

For handling show all examples.

## Buffer Object

```c++
#include <CmdBuffer.hpp>

CmdBuffer<32> myBuffer;
```

### Options
- ```setEndChar``` (default '\n') set character for stop reading. Normal is a line end.
