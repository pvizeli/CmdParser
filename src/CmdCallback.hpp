/* Copyright 2016 Pascal Vizeli <pascal.vizeli@syshack.ch>
 * BSD License
 *
 * https://github.com/pvizeli/CmdParser
 */

#ifndef CMDCALLBACK_H
#define CMDCALLBACK_H

#include <stdint.h>
#include <string.h>

#include <Arduino.h>

#include "CmdBuffer.hpp"
#include "CmdParser.hpp"

typedef void (*CmdCallFunct)();

/**
 *
 *
 */
class CmdCallbackObject
{
public:

    /**
     * Endless loop for process incoming data from serial.
     *
     * @param cmdBuffer         Buffer object for data handling
     * @param serial            Arduino serial interface from comming data
     */
    void loopCmdProcessing(CmdBufferObject *cmdBuffer, HardwareSerial *serial);

    /**
     * Search command in the buffer and execute the callback function.
     *
     * @param cmdStr            Cmd string to search
     * @return                  TRUE if found the command in the buffer
     */
    virtual bool processCmd(char *cmdStr) = 0;
};

/**
 *
 *
 */
template <size_t COUNTFUNCT>
class CmdCallback_P : public CmdCallbackObject
{
public:

    /**
     * Cleanup member data
     */
    CmdCallback_P() : m_nextElement(0) {
        memset(m_cmdList, 0x00, sizeof(PGM_P) * COUNTFUNCT);
        memset(m_functList, 0x00, sizeof(CmdCallFunct) * COUNTFUNCT);
    }

    /**
     * Link a callback function to command.
     *
     * @param cmdStr            A cmd string in progmem
     * @param cbFunct           A callback function to process your things
     * @return                  TRUE if you have space in buffer of object
     */
    bool addCmd(PGM_P cmdStr, CmdCallFunct cbFunct);

    /**
     * @implement CmdCallbackObject
     */
    virtual bool processCmd(char *cmdStr);

private:

    /** Array with list of commands */
    PGM_P           m_cmdList[COUNTFUNCT];

    /** List of function  */
    CmdCallFunct    m_functList[COUNTFUNCT];

    /** Pointer tof next element in array @see addCmd */
    size_t          m_nextElement;
};

#endif
