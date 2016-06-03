/* Copyright 2016 Pascal Vizeli <pvizeli@syshack.ch>
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

typedef void (*CmdCallFunct)(CmdParser *cmdParser);
typedef PGM_P CmdCallString_P;
typedef char *CmdCallString;

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
     * @param cmdParser         Parser object with options set
     * @param cmdBuffer         Buffer object for data handling
     * @param serial            Arduino serial interface from comming data
     */
    void loopCmdProcessing(CmdParser *cmdParser, CmdBufferObject *cmdBuffer,
                           HardwareSerial *serial);

    /**
     * Search command in the buffer and execute the callback function.
     *
     * @param cmdStr            Cmd string to search
     * @return                  TRUE if found the command in the buffer
     */
    virtual bool processCmd(CmdParser *cmdParser);

    /**
     * Give the size of callback store.
     *
     * @return                  Size of callback Store
     */
    virtual size_t getStoreSize() = 0;

    /**
     * Check is on store idx a valide cmd string and function.
     *
     * @param idx               Store number
     * @return                  TRUE if valid or FALSE
     */
    virtual bool checkStorePos(size_t idx) = 0;

    /**
     * Check if the cmd string equal to cmd in store.
     * Please check idx with @see checkStorePos befor you use this funct!
     *
     * @param idx               Store number
     * @param cmdStr            Cmd string to search
     * @return                  TRUE is equal
     */
    virtual bool equalStoreCmd(size_t idx, char *cmdStr) = 0;

    /**
     * Call function from store.
     * Please check idx with @see checkStorePos befor you use this funct!
     *
     * @param idx               Store number
     * @return                  TRUE if function is valid and calling
     */
    virtual bool callStoreFunct(size_t idx) = 0;
};

/**
 *
 *
 */
template <size_t STORESIZE, typename T>
class _CmdCallback : public CmdCallbackObject
{
  public:
    /**
     * Cleanup member data
     */
    _CmdCallback() : m_nextElement(0)
    {
        memset(m_cmdList, 0x00, sizeof(PGM_P) * STORESIZE);
        memset(m_functList, 0x00, sizeof(CmdCallFunct) * STORESIZE);
    }

    /**
     * Link a callback function to command.
     *
     * @param cmdStr            A cmd string in progmem
     * @param cbFunct           A callback function to process your things
     * @return                  TRUE if you have space in buffer of object
     */
    bool addCmd(T cmdStr, CmdCallFunct cbFunct);

    /**
     * @implement CmdCallbackObject
     */
    virtual size_t getStoreSize() { return STORESIZE; }

    /**
     * @implement CmdCallbackObject
     */
    virtual bool checkStorePos(size_t idx)
    {
        if (idx < STORESIZE && m_cmdList[idx] != NULL) {
            return true;
        }

        return false;
    }

    /**
     * @implement CmdCallbackObject
     */
    virtual bool callStoreFunct(size_t idx)
    {
        if (idx < STORESIZE && m_functList[idx] != NULL) {
            m_functList[idx]();
            return true;
        }

        return false;
    }

  protected:
    /** Array with list of commands */
    T m_cmdList[STORESIZE];

    /** List of function  */
    CmdCallFunct m_functList[STORESIZE];

    /** Pointer tof next element in array @see addCmd */
    size_t m_nextElement;
};

/**
 *
 *
 */
template <size_t STORESIZE>
class CmdCallback_P : public _CmdCallback<STORESIZE, CmdCallString_P>
{
    /**
     * @implement CmdCallbackObject with strcmp_P
     */
    virtual bool equalStoreCmd(size_t idx, char *cmdStr);
};

/**
 *
 *
 */
template <size_t STORESIZE>
class CmdCallback : public _CmdCallback<STORESIZE, CmdCallString>
{
    /**
     * @implement CmdCallbackObject with strcmp_P
     */
    virtual bool equalStoreCmd(size_t idx, char *cmdStr);
};

#endif
