
#include "CmdBuffer.hpp"

CmdParser::CmdParser() :
    m_ignoreQuote(false),
    m_setCmdUpper(true),
    m_seperator(CMDPARSER_CHAR_SP),
    m_buffer(NULL),
    m_bufferSize(0),
    m_paramCount(0)
{

}

uint16_t CmdParser::parseCmd(uint8_t *buffer, site_t bufferSize)
{
    bool    isString    = false;

    // init param count
    m_paramCount ^= m_paramCount;

    // buffer is not okay
    if (buffer == NULL || bufferSize == 0) {
        return m_paramCount;
    }

    // init buffer
    m_buffer        = buffer;
    m_bufferSize    = bufferSize;

    ////
    // Run Parser
    for (size_t i = 0; i < bufferSize; i++) {

        // end
        if (buffer[i] == 0x00) {
            return m_paramCount;
        }
        // is string "xy zyx" / only the quote option is disabled
        else if (!m_ignoreQuote && buffer[i] == CMDPARSER_CHAR_DQ) {
            buffer[i] = 0x00;
            isString = !isString;
        }
        // replace seperator with '\0'
        else if (!isString && buffer[i] == m_seperator) {
                buffer[i] = 0x00;
        }

        // count
        if (i > 0 && buffer[i] == 0x00 && buffer[i-1] != 0x00) {
            m_paramCount++;
        }
    }

    return m_paramCount;
}

char* CmdParser::getCommand()
{
    // upper case active
    if (m_setCmdUpper) {
        return this->getCmdParamUpper(0);
    }

    // not convert any character
    return this->getCmdParam(0);
}

char* CmdParser::getCmdParam(uint16_t idx)
{
    uint16_t count = 0;

    // search hole cmd buffer
    for (size_t i = 0; i < m_bufferSize; i++) {

        // find next position
        if (i > 0 && m_buffer[i] == 0x00 && m_buffer[i-1] != 0x00) {
            count++;
        }

        // found indx with next character
        if (count == indx && m_buffer[i] != 0x00) {
            return &m_buffer[i];
        }
    }

    return NULL;
}

char* CmdParser::getCmdParamUpper(uint16_t idx)
{
    char *element = this->getCmdParam(idx);

    // not found?
    if (element == NULL) {
        return NULL;
    }

    for (size_t i = 0; element[i] != 0x00; i++) {
        // set upper
        element[i] = toupper(element[i]);
    }

    return element;
}
