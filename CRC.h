#pragma once
#ifndef CRC_ARDUINO_H
#define CRC_ARDUINO_H

#ifdef __AVR__
#include <util/crc16.h>
#endif

namespace CRC
{
    uint8_t crc8(const uint8_t *buff, size_t size)
    {
        uint8_t* p = (uint8_t*)buff;
        uint8_t result = 0;

        for (; size != 0 ; size--)
        {
            result ^= *p++;

            for (size_t i = 0 ; i < 8; i++)
            {
                if (result & 0x80)
                {
                    result <<= 1;
                    result ^= 0x85; // x8 + x7 + x2 + x0
                }
                else
                {
                    result <<= 1;
                }
            }
        }
        return result;
    }

    uint16_t crc16(const uint8_t* buff, size_t size)
    {
        uint16_t result = 0xFFFF;

        for (size_t i = 0; i < size; ++i)
        {
#ifdef __AVR__
            result = _crc16_update(result, buff[i]);
#else
            result ^= buff[i];
            for (size_t j = 0; j < 8; ++j)
            {
                if (result & 0x01) result = (result >> 1) ^ 0xA001;
                else result >>= 1;
            }
#endif
        }
        return result;
    }

}

#endif // CRC_ARDUINO_H
