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


#ifndef INLINE
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
#endif


#ifdef __arm__
    #if defined(CORE_TEENSY) && !defined(__TEENSY__)
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
#ifndef __AXIS__
#define __AXIS__                                0x00
#endif
#ifndef __X_AXIS__
#define __X_AXIS__                              0x01
#endif
#ifndef __Y_AXIS__
#define __Y_AXIS__                              0x02
#endif
#ifndef __Z_AXIS__
#define __Z_AXIS__                              0x03
#endif


// State
#ifndef __WAKE__
#define __WAKE__                                0x01
#endif
#ifndef __SLEEP__
#define __SLEEP__                               0x02
#endif


// Communication Protocols
#ifndef __COMMUNICATION_PROTOCOLS__
#define __COMMUNICATION_PROTOCOLS__             0x8000000000000000
#endif
#ifndef __SERIAL__
#define __SERIAL__                              0x8000000000000001
#endif
#ifndef __I2C__
#define __I2C__                                 0x8000000000000002
#endif
#ifndef __SPI__
#define __SPI__                                 0x8000000000000003
#endif


// Sensors and Input Devices Groups
#ifndef __SENSORS__INPUT_DEVICES__GROUPS
#define __SENSORS__INPUT_DEVICES__GROUPS        0x4000000000000000
#endif
#ifndef __GPS__
#define __GPS__                                 0x4000010000000000
#endif
#ifndef __CAMERA__
#define __CAMERA__                              0x4000020000000000
#endif


// Sensors and Input Devices
#ifndef __SENSORS__INPUT_DEVICES__
#define __SENSORS__INPUT_DEVICES__              0x2000000000000000
#endif
#ifndef __BME280__
#define __BME280__                              0x2000000000010000
#endif
#ifndef __BNO055__
#define __BNO055__                              0x2000000000020000
#endif
#ifndef __MTK3339__
#define __MTK3339__                             0x2000000000030000
#endif
#ifndef __OV5642__
#define __OV5642__                              0x2000000000040000
#endif


// Output Devices
#ifndef __OUTPUT_DEVICES__
#define __OUTPUT_DEVICES__                      0x1000000000000000
#endif
#ifndef __TTY__
#define __TTY__                                 0x1000000000010000
#endif


// Oriental Data Types
#ifndef __ORIENTAL_DATA_TYPES__
#define __ORIENTAL_DATA_TYPES__                 0x0080000000000000
#endif
#ifndef __ROTATIONAL_ANGLE__
#define __ROTATIONAL_ANGLE__                    0x0080000000000100
#endif
#ifndef __ANGULAR_VELOCITY__
#define __ANGULAR_VELOCITY__                    0x0080000000000200
#endif
#ifndef __GRAVITATIONAL_ACCELERATION__
#define __GRAVITATIONAL_ACCELERATION__          0x0080000000000300
#endif
#ifndef __LINEAR_ACCELERATION__
#define __LINEAR_ACCELERATION__                 0x0080000000000400
#endif
#ifndef __LINEAR_VELOCITY__
#define __LINEAR_VELOCITY__                     0x0080000000000500
#endif
#ifndef __LINEAR_DISPLACEMENT__
#define __LINEAR_DISPLACEMENT__                 0x0080000000000600
#endif
#ifndef __MAGNETISM__
#define __MAGNETISM__                           0x0080000000000700
#endif


// Non Oriental Data Types
#ifndef __NON_ORIENTAL_DATA_TYPES__
#define __NON_ORIENTAL_DATA_TYPES__             0x0040000000000000
#endif
#ifndef __TEMPERATURE__
#define __TEMPERATURE__                         0x0040000000000001
#endif
#ifndef __HUMIDITY__
#define __HUMIDITY__                            0x0040000000000002
#endif
#ifndef __PRESSURE__
#define __PRESSURE__                            0x0040000000000003
#endif
#ifndef __LATITUDE__
#define __LATITUDE__                            0x0040000000000004
#endif
#ifndef __LONGITUDE__
#define __LONGITUDE__                           0x0040000000000005
#endif
#ifndef __ALTITUDE__
#define __ALTITUDE__                            0x0040000000000006
#endif



INLINE bool IsCommunicationProtocol(uint64_t dataType) {
    return (dataType >> 63);
}
INLINE uint64_t GetCommunicationProtocol(uint64_t dataType) {
    return (dataType & 0x800000000000FFFF);
}


INLINE bool IsSensorInputDeviceGroup(uint64_t dataType) {
    return (dataType << 1) >> 63;
}
INLINE bool GetSensorInputDeviceGroup(uint64_t dataType) {
    return (dataType & 0x4000FF0000000000);
}


INLINE bool IsSensorInputDevice(uint64_t dataType) {
    return (dataType << 2) >> 63;
}
INLINE bool GetSensorInputDevice(uint64_t dataType) {
    return (dataType & 0x200000FFFFFF0000);
}


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