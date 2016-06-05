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
const uint8_t  CMDPARSER_CHAR_DQ = 0x22;
const uint8_t  CMDPARSER_CHAR_EQ = 0x3D;
const uint16_t CMDPARSER_ERROR   = 0xFFFF;

typedef PGM_P       CmdParserString_P;
typedef const char *CmdParserString;

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
     *
     * @return                  String with cmd word or NULL if not exists
     */
    char *getCommand() { return this->getCmdParam(0); }

    /**
     * Get the param IDX from command line.
     *
     * @param idx               Number of param to get
     * @return                  String with param or NULL if not exists
     */
    char *getCmdParam(uint16_t idx);

    /**
     * Return the counter of parameter from cmd.
     *
     * @return                  Return the param counter of command
     */
    uint16_t getParamCount() { return m_paramCount; }

    /**
     * If KeyValue option is set, search the value from a key pair.
     * KEY=Value i.e. KEY is upper case @see setOptCmdUpper.
     *
     * @param key               Key for search in cmd
     * @return                  String with value or NULL if not exists
     */
    char *getValueFromKey(CmdParserString key)
    {
        return this->getValueFromKey(key, false);
    }

    /**
     * Check if param equal with value case sensitive.
     *
     * @param idx               Number of param to get
     * @param value             String to compare
     * @return                  TRUE is equal
     */
    bool equalCmdParam(uint16_t idx, CmdParserString value)
    {
        if (strcasecmp(this->getCmdParam(idx), value) == 0) {
            return true;
        }

        return false;
    }

    /**
     * Check if param equal with value case sensitive.
     *
     * @param idx               Number of param to get
     * @param value             String to compare in PROGMEM
     * @return                  TRUE is equal
     */
    bool equalCmdParam_P(uint16_t idx, CmdParserString_P value)
    {
        if (strcasecmp_P(this->getCmdParam(idx), value) == 0) {
            return true;
        }

        return false;
    }

    /**
     * Check if command equal with value case sensitive.
     *
     * @param value             String to compare
     * @return                  TRUE is equal
     */
    bool equalCommand(CmdParserString value)
    {
        return this->equalCmdParam(0, value);
    }

    /**
     * Check if command equal with value case sensitive.
     *
     * @param value             String to compare in PROGMEM
     * @return                  TRUE is equal
     */
    bool equalCommand_P(CmdParserString_P value)
    {
        return this->equalCmdParam_P(0, value);
    }

    /**
     * If KeyValue option is set, search the value from a key pair.
     * KEY=Value i.e. KEY is upper case @see setOptCmdUpper.
     *
     * @param key               Key store in PROGMEM for search in cmd
     * @return                  String with value or NULL if not exists
     */
    char *getValueFromKey_P(CmdParserString_P key)
    {
        return this->getValueFromKey(key, true);
    }

    /**
     * Set parser option to ignore " quote for string.
     * Default is off
     *
     * @param onOff             Set option TRUE (on) or FALSE (off)
     */
    void setOptIgnoreQuote(bool onOff = true) { m_ignoreQuote = onOff; }

    /**
     * Set parser option for handling KEY=Value parameter.
     * Default is off
     *
     * @param onOff             Set option TRUE (on) or FALSE (off)
     */
    void setOptKeyValue(bool onOff = false) { m_useKeyValue = onOff; }

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

    /** Parser option @see setOptKeyValue */
    bool m_useKeyValue;

    /** Parser option @see setOptSeperator */
    char m_seperator;

    /** Pointer to cmd buffer */
    uint8_t *m_buffer;

    /** Size of cmd buffer */
    size_t m_bufferSize;

    /** Number of parsed params */
    uint16_t m_paramCount;

    /**
     * Handle internal key value search function.
     *
     * @param progmem           TRUE key is store in progmem
     * @return                  String with value or NULL if not exists
     */
    char *getValueFromKey(const char *key, bool progmem);
};

#endif
