/* Copyright 2016 Pascal Vizeli <pvizeli@syshack.ch>
 * BSD License
 *
 * https://github.com/pvizeli/CmdParser
 */
 
#include "CmdCallback.hpp"

void CmdCallbackObject::loopCmdProcessing(CmdParser *cmdParser,
                                          CmdBufferObject *cmdBuffer,
                                          HardwareSerial *serial)
{
    do {
        // read data
        if (cmdBuffer->readFromSerial(serial)) {

            // parse command line
            if (cmdParser->parseCmd(cmdBuffer) != CMDPARSER_ERROR) {
                // search command in store and call function
                if (this->processCmd(cmdParser)) {
                    // FIXME: handling cmd not found
                }
            }
        }
    } while (true);
}

bool CmdCallbackObject::processCmd(CmdParser *cmdParser)
{
    char *cmdStr = cmdParser->getCommand();

    // check is commando okay
    if (cmdStr == NULL) {
        return false;
    }

    // search cmd in store
    for (size_t i = 0;
        i < this->getStoreSize() && this->checkStorePos(i);
        i++) {

        // compare command with string
        if (this->equalStoreCmd(i, cmdStr)) {
            // call function
            this->callStoreFunct(i);
            return true;
        }
    }

    return false;
}

template <size_t COUNTFUNCT>
bool CmdCallback_P<COUNTFUNCT>::addCmd(PGM_P cmdStr, CmdCallFunct cbFunct)
{
    // Store is full
    if (m_nextElement >= COUNTFUNCT) {
        return false;
    }

    // add to store
    m_cmdList[m_nextElement]    = cmdStr;
    m_functList[m_nextElement]  = cbFunct;

    ++m_nextElement;
    return true;
}

template <size_t COUNTFUNCT>
bool CmdCallback<COUNTFUNCT>::addCmd(char *cmdStr, CmdCallFunct cbFunct)
{
    // Store is full
    if (m_nextElement >= COUNTFUNCT) {
        return false;
    }

    // add to store
    m_cmdList[m_nextElement]    = cmdStr;
    m_functList[m_nextElement]  = cbFunct;

    ++m_nextElement;
    return true;
}
