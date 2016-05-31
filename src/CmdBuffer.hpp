// Copyright 2016 Pascal Vizeli <pascal.vizeli@syshack.ch>
// BSD License
//
// https://github.com/pvizeli/CmdBuffer

#ifndef CMDBUFFER_H
#define CMDBUFFER_H

#include <stdint.h>
#include <string.h>
#include <Arduino.h>


#define CMDBUFFER_CHAR_PRINTABLE 0xF1
#define CMDBUFFER_CHAR_LF 0x0A
#define CMDBUFFER_CHAR_CR 0x0D

/**
 *
 *
 */
template <size_t BUFFERSIZE>
class CmdBuffer
{
public:

    /**
     * Set serial object an clear buffer.
     */
    explicit CmdBuffer(HardwareSerial *serial);

    /**
     * Read data from serial communication to buffer.
     *
     * @param timeOut       Set a time out in millisec or 0 for none
     * @return              TRUE if data readed until end character or FALSE
     *                      is a timeout receive or buffer is full.
     */
    bool readFromSerial(uint32_t timeOut = 0);

    /**
     * Clear buffer with 0x00
     */
    void clear() {
        memset(m_buffer, 0x00, BUFFERSIZE + 1);
    }

    /**
     * Return a 0x00 terminatet string
     *
     * @return             String from Buffer
     */
    uint8_t* getCmd() {
        return m_buffer;
    }

    /**
     * Set a ASCII character for serial cmd end.
     " Default value is LF.
     *
     * Macros for helping are:
     * - CMDBUFFER_CHAR_LF
     * - CMDBUFFER_CHAR_CR
     *
     * @param end       ASCII character
     */
    void setEndChar(uint8_t end) {
        m_endChar = end;
    }

private:

    /** Buffer for reading data from serial input */
    uint8_t     m_buffer[BUFFERSIZE+1];

    /** Arduino serial object */
    HardwareSerial *m_serial;

    /** Character for handling the end of serial data communication */
    uint8_t     m_endChar;
};

#endif
