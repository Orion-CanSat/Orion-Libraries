#pragma once

#include <stdint.h>

#ifndef NAN
    #define NAN (float)0xFFFFFFFF
#endif
#ifndef INF
    #define INF (float)0b01111111100000000000000000000000
#endif
#ifndef PI
    #define PI (float)3.1415926535897932384626433832795
#endif


#ifdef _MSC_VER
    #define INLINE __forceinline
#elif defined(__GNUC__)
    #define INLINE inline __attribute__((__always_inline__))
#elif defined(__CLANG__)
    #if __has_attribute(__always_inline__)
        #define INLINE inline __attribute__((__always_inline__))
    #else
        #define INLINE inline
    #endif
#else
    #define INLINE inline
#endif


#ifdef __arm__
    #ifdef CORE_TEENSY
        #define __TEENSY__
        #if defined(__AT90USB162__)
            #define __TEENSY_1_0__
        #elif defined(__ATMEGA32U4__)
            #define __TEENSY_2_0__
        #elif defined(__MKL26Z64__)
            #define __TEENSY_LC__
        #elif defined(__MK20DX128__)
            #define __TEENSY_3_0__
        #elif defined(__MK20DX256__)
            #define __TEENSY_3_1__
            #define __TEENSY_3_2__
        #elif defined(__MK64FX512__)
            #define __TEENSY_3_5__
        #elif defined(__MK66FX1M0__)
            #define __TEENSY_3_6__
        #elif defined(__IMXRT1062__)
            #if defined(BUILTIN_SDCARD)
                #define __TEENSY_4_1__
            #else
                #define __TEENSY_4_0__
            #endif
        #endif
    #endif
#endif


// AXIS
#define __AXIS__                                0x00
#define __X_AXIS__                              0x01
#define __Y_AXIS__                              0x02
#define __Z_AXIS__                              0x03

// Communication Protocols
#define __COMMUNICATION_PROTOCOLS__             0x8000000000000000
#define __SERIAL__                              0x8000000000000001
#define __I2C__                                 0x8000000000000002
#define __SPI__                                 0x8000000000000003

// Sensors and Input Devices
#define __SENSORS__INPUT_DEVICES__              0x2000000000000000
#define __BME280__                              0x2000000000010000
#define __BNO055__                              0x2000000000020000

// Sensors and Input Devices Groups
#define __SENSORS__INPUT_DEVICES__GROUPS        0x4000000000000000
#define __GPS__                                 0x4000010000000000

// Output Devices
#define __OUTPUT_DEVICES__                      0x1000000000000000
#define __TTY__                                 0x1000000000010000

// Oriental Data Types
#define __ORIENTAL_DATA_TYPES__                 0x0080000000000000
#define __ROTATIONAL_ANGLE__                    0x0080000000000100
#define __ANGULAR_VELOCITY__                    0x0080000000000200
#define __GRAVITATIONAL_ACCELERATION__          0x0080000000000300
#define __LINEAR_ACCELEATION__                  0x0080000000000400
#define __LINEAR_VELOCITY__                     0x0080000000000500
#define __LINEAR_DISPLACEMENT__                 0x0080000000000600
#define __MAGNETISM__                           0x0080000000000700

// Non Oriental Data Types
#define __NON_ORIENTAL_DATA_TYPES__             0x0040000000000000
#define __TEMPERATURE__                         0x0040000000000001
#define __HUMIDITY__                            0x0040000000000002
#define __PRESSURE__                            0x0040000000000003
#define __LONGITUDE__                           0x0040000000000004
#define __LATITUDE__                            0x0040000000000005
#define __ALTITUDE__                            0x0040000000000006


INLINE bool IsOrientalDataType(uint64_t dataType) {
    return (dataType & __ORIENTAL_DATA_TYPES__) == __ORIENTAL_DATA_TYPES__;
}

INLINE bool IsNonOrientalDataType(uint64_t dataType) {
    return (dataType & __NON_ORIENTAL_DATA_TYPES__) == __NON_ORIENTAL_DATA_TYPES__;
}

INLINE bool IsDataType(uint64_t dataType) {
    return IsOrientalDataType(dataType) || IsNonOrientalDataType(dataType);
}

INLINE int8_t GetAxis(uint64_t dataType) {
    if (!IsDataType(dataType))
        return -1;
    
    dataType <<= 56;
    dataType >>= 56;

    return dataType;
}