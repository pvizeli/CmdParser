/* Copyright 2016 Pascal Vizeli <pvizeli@syshack.ch>
 * BSD License
 *
 * https://github.com/pvizeli/CmdParser
 */

#ifndef CMDPARSER_H
#define CMDPARSER_H

#include <ctype.h>

#include "CmdBuffer.hpp"

const uint8_t  CMDPARSER_CHAR_SP = 0x20;
const uint8_t  CMDPARSER_CHAR_DQ = 0x20;
const uint16_t CMDPARSER_ERROR   = 0xFFFF;

/**
 *
 *
 */
class CmdParser
{
  public:
    /**
     * Set member to default values.
     */
    CmdParser();

    /**
     * Parse a buffer with commands.
     * @warning This function change the buffer and only this object can handle
     * the new buffer!
     *
     * @param buffer            Buffer with cmd string
     * @param bufferSize        Size of buffer
     * @return                  Number of params or CMDPARSER_ERROR
     */
    uint16_t parseCmd(uint8_t *buffer, size_t bufferSize);

    uint16_t parseCmd(CmdBufferObject *cmdBuffer)
    {
        return this->parseCmd(cmdBuffer->getBuffer(),
                              cmdBuffer->getBufferSize());
    }

    uint16_t parseCmd(char *cmdStr)
    {
        return this->parseCmd(reinterpret_cast<uint8_t *>(cmdStr),
                              strlen(cmdStr));
    }

    /**
     * Get the initial command line word.
     * For options with this function @see setOptCmdUpper
     *
     * @return                  String with cmd word or NULL if not exists
     */
    char *getCommand();

    /**
     * Get the param IDX from command line.
     *
     * @param idx               Number of param to get
     * @return                  String with param or NULL if not exists
     */
    char *getCmdParam(uint16_t idx);

    /**
     * Get the param IDX from command line and change it to upper case.
     * It change the cmd buffer permanent to upper case!
     *
     * @param idx               Number of param to get
     * @return                  String with param or NULL if not exists
     */
    char *getCmdParamUpper(uint16_t idx);

    /**
     * Return the counter of parameter from cmd.
     *
     * @return                  Return the param counter of command
     */
    uint16_t getParamCount() { return m_paramCount; }

    /**
     * Set parser option to ignore " quote for string.
     * Default is off
     *
     * @param onOff             Set option TRUE (on) or FALSE (off)
     */
    void setOptIgnoreQuote(bool onOff = true) { m_ignoreQuote = onOff; }

    /**
     * Set parser option to upper the command to upper case.
     * Default is on
     *
     * @param onOff             Set option TRUE (on) or FALSE (off)
     */
    void setOptCmdUpper(bool onOff = false) { m_ignoreQuote = onOff; }

    /**
     * Set parser option for cmd seperator.
     * Default is ' ' or CMDPARSER_CHAR_SP
     *
     * @param seperator         Set character for seperator cmd
     */
    void setOptSeperator(char seperator) { m_seperator = seperator; }

  private:
    /** Parser obtion @see setOptIgnoreQuote */
    bool m_ignoreQuote;

    /** Parser option @see setOptCmdUpper */
    bool m_setCmdUpper;

    /** Parser option @see setOptSeperator */
    char m_seperator;

    /** Pointer to cmd buffer */
    uint8_t *m_buffer;

    /** Size of cmd buffer */
    size_t m_bufferSize;

    /** Number of parsed params */
    uint16_t m_paramCount;
};

#endif
