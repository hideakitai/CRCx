#pragma once

#ifndef HT_UTIL_CRC_WRAPPER_H
#define HT_UTIL_CRC_WRAPPER_H

#ifdef ARDUINO
#include <Arduino.h>
#if defined(KINETISK)
#include "libs/FastCRC/FastCRChw.h"
#else
#include "libs/FastCRC/FastCRCsw.h"
#endif
#else
#define CRCPP_USE_CPP11
#define CRCPP_USE_NAMESPACE
#define CRCPP_INCLUDE_ESOTERIC_CRC_DEFINITIONS
#include "libs/CRCpp/CRC.h"
#endif

namespace ht {
namespace util {
    namespace crc {

        enum class Crc8 : uint8_t {
            SMBUS,
            MAXIM
        };

        enum class Crc16 : uint8_t {
            CCITT,
            KERMIT,
            MODBUS,
            XMODEM,
            X25
        };

        enum class Crc32 : uint8_t {
            CRC32,
            POSIX
        };

#ifdef ARDUINO

        namespace fastcrc {
            inline uint8_t crc8(const uint8_t* data, const size_t size, const Crc8 type = Crc8::SMBUS) {
                static FastCRC8 fastcrc;
                switch (type) {
                    case Crc8::SMBUS: return fastcrc.smbus(data, size);
                    case Crc8::MAXIM: return fastcrc.maxim(data, size);
                }
                return 0xFF;
            }

            inline uint16_t crc16(const uint8_t* data, const size_t size, const Crc16 type = Crc16::MODBUS) {
                static FastCRC16 fastcrc;
                switch (type) {
                    case Crc16::CCITT: return fastcrc.ccitt(data, size);
                    case Crc16::KERMIT: return fastcrc.kermit(data, size);
                    case Crc16::MODBUS: return fastcrc.modbus(data, size);
                    case Crc16::XMODEM: return fastcrc.xmodem(data, size);
                    case Crc16::X25: return fastcrc.x25(data, size);
                }
                return 0xFFFF;
            }

            inline uint32_t crc32(const uint8_t* data, const size_t size, const Crc32 type = Crc32::CRC32) {
                static FastCRC32 fastcrc;
                switch (type) {
                    case Crc32::CRC32: return fastcrc.crc32(data, size);
                    case Crc32::POSIX: return fastcrc.cksum(data, size);
                }
                return 0xFFFFFFFF;
            }

            inline uint8_t crc8_update(const uint8_t* data, const size_t size, const Crc8 type = Crc8::SMBUS) {
                static FastCRC8 fastcrc;
                static bool has_initialized {false};
                if (!has_initialized) {
                    has_initialized = true;
                    switch (type) {
                        case Crc8::SMBUS: return fastcrc.smbus(data, size);
                        case Crc8::MAXIM: return fastcrc.maxim(data, size);
                    }
                } else {
                    switch (type) {
                        case Crc8::SMBUS: return fastcrc.smbus_upd(data, size);
                        case Crc8::MAXIM: return fastcrc.maxim_upd(data, size);
                    }
                }
                return 0xFF;
            }

            inline uint16_t crc16_update(const uint8_t* data, const size_t size, const Crc16 type = Crc16::MODBUS) {
                static FastCRC16 fastcrc;
                static bool has_initialized {false};
                if (!has_initialized) {
                    has_initialized = true;
                    switch (type) {
                        case Crc16::CCITT: return fastcrc.ccitt(data, size);
                        case Crc16::KERMIT: return fastcrc.kermit(data, size);
                        case Crc16::MODBUS: return fastcrc.modbus(data, size);
                        case Crc16::XMODEM: return fastcrc.xmodem(data, size);
                        case Crc16::X25: return fastcrc.x25(data, size);
                    }
                } else {
                    switch (type) {
                        case Crc16::CCITT: return fastcrc.ccitt_upd(data, size);
                        case Crc16::KERMIT: return fastcrc.kermit_upd(data, size);
                        case Crc16::MODBUS: return fastcrc.modbus_upd(data, size);
                        case Crc16::XMODEM: return fastcrc.xmodem_upd(data, size);
                        case Crc16::X25: return fastcrc.x25_upd(data, size);
                    }
                }
                return 0xFFFF;
            }

            inline uint32_t crc32_update(const uint8_t* data, const size_t size, const Crc32 type = Crc32::CRC32) {
                static FastCRC32 fastcrc;
                static bool has_initialized {false};
                if (!has_initialized) {
                    has_initialized = true;
                    switch (type) {
                        case Crc32::CRC32: return fastcrc.crc32(data, size);
                        case Crc32::POSIX: return fastcrc.cksum(data, size);
                    }
                } else {
                    switch (type) {
                        case Crc32::CRC32: return fastcrc.crc32_upd(data, size);
                        case Crc32::POSIX: return fastcrc.cksum_upd(data, size);
                    }
                }
                return 0xFFFFFFFF;
            }

        }  // namespace fastcrc

        using namespace fastcrc;
#else

        namespace crcpp {
            using crc8_t = CRCPP::CRC::Parameters<crcpp_uint8, 8>;
            using crc16_t = CRCPP::CRC::Parameters<crcpp_uint16, 16>;
            using crc32_t = CRCPP::CRC::Parameters<crcpp_uint32, 32>;
            using crc64_t = CRCPP::CRC::Parameters<crcpp_uint64, 64>;

            inline crc8_t get_crc8_param(const Crc8 type) {
                switch (type) {
                    case Crc8::SMBUS: return std::move(CRCPP::CRC::CRC_8());
                    case Crc8::MAXIM: return std::move(CRCPP::CRC::CRC_8_MAXIM());
                }
                return std::move(CRCPP::CRC::CRC_8());
            }

            inline crc16_t get_crc16_param(const Crc16 type) {
                switch (type) {
                    case Crc16::CCITT: return std::move(CRCPP::CRC::CRC_16_CCITTFALSE());
                    case Crc16::KERMIT: return std::move(CRCPP::CRC::CRC_16_KERMIT());
                    case Crc16::MODBUS: return std::move(CRCPP::CRC::CRC_16_MODBUS());
                    case Crc16::XMODEM: return std::move(CRCPP::CRC::CRC_16_XMODEM());
                    case Crc16::X25: return std::move(CRCPP::CRC::CRC_16_X25());
                }
                return std::move(CRCPP::CRC::CRC_16_MODBUS());
            }

            inline crc32_t get_crc32_param(const Crc32 type) {
                switch (type) {
                    case Crc32::CRC32: return std::move(CRCPP::CRC::CRC_32());
                    case Crc32::POSIX: return std::move(CRCPP::CRC::CRC_32_POSIX());
                }
                return std::move(CRCPP::CRC::CRC_32());
            }

            inline uint8_t crc8(const uint8_t* data, const size_t size, const Crc8 type = Crc8::SMBUS) {
                auto param = get_crc8_param(type);
                return CRCPP::CRC::Calculate(data, size, param);
            }

            inline uint16_t crc16(const uint8_t* data, const size_t size, const Crc16 type = Crc16::MODBUS) {
                auto param = get_crc16_param(type);
                return CRCPP::CRC::Calculate(data, size, param);
            }

            inline uint32_t crc32(const uint8_t* data, const size_t size, const Crc32 type = Crc32::CRC32) {
                auto param = get_crc32_param(type);
                return CRCPP::CRC::Calculate(data, size, param);
            }

            inline uint64_t crc64(const uint8_t* data, const size_t size) {
                return CRCPP::CRC::Calculate(data, size, CRCPP::CRC::CRC_64());
            }

            inline uint8_t crc8_update(const uint8_t* data, const size_t size, const Crc8 type = Crc8::SMBUS) {
                static auto param = get_crc8_param(type);
                static bool has_initialized {false};
                static uint8_t result {0};
                if (!has_initialized) {
                    has_initialized = true;
                    result = CRCPP::CRC::Calculate(data, size, param);
                } else {
                    result = CRCPP::CRC::Calculate(data, size, param, result);
                }
                return result;
            }

            inline uint16_t crc16_update(const uint8_t* data, const size_t size, const Crc16 type = Crc16::MODBUS) {
                static auto param = get_crc16_param(type);
                static bool has_initialized {false};
                static uint16_t result {0};
                if (!has_initialized) {
                    has_initialized = true;
                    result = CRCPP::CRC::Calculate(data, size, param);
                } else {
                    result = CRCPP::CRC::Calculate(data, size, param, result);
                }
                return result;
            }

            inline uint32_t crc32_update(const uint8_t* data, const size_t size, const Crc32 type = Crc32::CRC32) {
                static auto param = get_crc32_param(type);
                static bool has_initialized {false};
                static uint32_t result {0};
                if (!has_initialized) {
                    has_initialized = true;
                    result = CRCPP::CRC::Calculate(data, size, param);
                } else {
                    result = CRCPP::CRC::Calculate(data, size, param, result);
                }
                return result;
            }

            inline uint64_t crc64_update(const uint8_t* data, const size_t size) {
                static auto param = CRCPP::CRC::CRC_64();
                static bool has_initialized {false};
                static uint64_t result {0};
                if (!has_initialized) {
                    has_initialized = true;
                    result = CRCPP::CRC::Calculate(data, size, param);
                } else {
                    result = CRCPP::CRC::Calculate(data, size, param, result);
                }
                return result;
            }
        }  // namespace crcpp

        using namespace crcpp;
#endif

    }  // namespace crc
}  // namespace util
}  // namespace ht

namespace crcx = ht::util::crc;

#endif  // HT_UTIL_CRC_WRAPPER_H
