/* Copyright 2016 Pascal Vizeli <pvizeli@syshack.ch>
 * BSD License
 *
 * https://github.com/pvizeli/CmdParser
 */

#include "CmdCallback.hpp"

void CmdCallbackObject::loopCmdProcessing(CmdParser *      cmdParser,
                                          CmdBufferObject *cmdBuffer,
                                          HardwareSerial * serial)
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
    for (size_t i = 0; this->checkStorePos(i); i++) {

        // compare command with string
        if (this->equalStoreCmd(i, cmdStr)) {
            // call function
            return this->callStoreFunct(i);
        }
    }

    return false;
}

template <size_t STORESIZE, typename T>
bool _CmdCallback<STORESIZE, T>::addCmd(T cmdStr, CmdCallFunct cbFunct)
{
    // Store is full
    if (m_nextElement >= STORESIZE) {
        return false;
    }

    // add to store
    m_cmdList[m_nextElement]   = cmdStr;
    m_functList[m_nextElement] = cbFunct;

    ++m_nextElement;
    return true;
}

template <size_t STORESIZE>
bool CmdCallback<STORESIZE>::equalStoreCmd(size_t idx, char *cmdStr)
{
    if (this->checkStorePos(idx) &&
        strcasecmp(this->m_cmdList[idx], cmdStr) == 0) {
        return true;
    }

    return false;
}

template <size_t STORESIZE>
bool CmdCallback_P<STORESIZE>::equalStoreCmd(size_t idx, char *cmdStr)
{
    if (this->checkStorePos(idx) &&
        strcasecmp_P(this->m_cmdList[idx], cmdStr) == 0) {
        return true;
    }

    return false;
}
