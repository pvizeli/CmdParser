/* Copyright 2016 Pascal Vizeli <pvizeli@syshack.ch>
 * BSD License
 *
 * https://github.com/pvizeli/CmdParser
 */

#include "CmdBuffer.hpp"

bool CmdBufferObject::readFromSerial(Stream *serial, uint32_t timeOut)
{
    uint32_t isTimeOut;
    uint32_t startTime;
    uint8_t  readChar;
    uint8_t *buffer = this->getBuffer();
    bool     over   = false;

    // UART initialize?
    if (serial == NULL) {
        return false;
    }

    ////
    // Calc Timeout
    if (timeOut != 0) {
        startTime = millis();
        isTimeOut = startTime + timeOut;

        // overloaded
        if (isTimeOut < startTime) {
            over = true;
        } else {
            over = false;
        }
    }

    ////
    // process serial reading
    do {

        // if data in serial input buffer
        while (serial->available()) {

            // is buffer full?
            if (m_dataOffset >= this->getBufferSize()) {
                m_dataOffset = 0;
                return false;
            }

            // read into buffer
            readChar = serial->read();

            // is that the end of command
            if (readChar == m_endChar) {
                buffer[m_dataOffset] = '\0';
                m_dataOffset         = 0;
                return true;
            }

            // is a printable character
            if (readChar > CMDBUFFER_CHAR_PRINTABLE) {
                buffer[m_dataOffset++] = readChar;
            }
        }

        // Timeout is active?
        if (timeOut != 0) {
            // calc diff timeout
            if (over) {
                if (startTime > millis()) {
                    over = false;
                }
            }

            // timeout is receive
            if (isTimeOut <= millis() && !over) {
                return false;
            }
        }

    } while (true); // timeout

    return false;
}
