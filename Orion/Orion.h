#pragma once

#include <float.h>
#include <stdint.h>

#ifndef NULL
    #define NULL (void*)0x00
#endif

#ifndef NAN
    #define NAN (float)0xFFFFFFFF
#endif

#ifndef INF
    #define INF (float)0x7f800000
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


#if defined(__arm__)
    #if defined(CORE_TEENSY)
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
        #endif//Teensy Detector
    #endif//CORE_TEENSY
#endif//__arm__


//AXIS
#define __X_AXIS__                          0x01
#define __Y_AXIS__                          0x02
#define __Z_AXIS__                          0x03

//State
#define __WAKE__                            0x01
#define __SLEEP__                           0x02

//Communication Protocols
#define __COMMMUNICATION_PROTOCOLS__        0x8000000000000000
#define __SERIAL__                          0x8000000000000001
#define __I2C__                             0x8000000000000002
#define __SPI__                             0x8000000000000003

//Sensor & Input Devices Groups
#define __GPS__                             0x010000
#define __CAMERA__                          0x020000

//Sensors & Input Devices
#define __SENSORS__INPUT_DEVICES__          0x4000000000000000
#define __BME_280__                         0x4000000000000001
#define __BNO_055__                         0x4000000000000002
#define __MTK3339__                         0x4000000000000003
#define __OV5642__                          0x4000000000000004

//Output Devices
#define __OUTPUT_DEVICE__                   0xC000000000000000
#define __TTY__                             0xC000000000000001

//Data Types Non Orientational
#define __DATA_TYPES_NON_ORIENTATIONAL__    0x2000000000000000
#define __TEMPERATURE__                     0x2000000000000001
#define __HUMIDITY__                        0x2000000000000002
#define __PRESSURE__                        0x2000000000000003
#define __ALTITUDE__                        0x2000000000000004

//Data Types Orientational
#define __DATA_TYPES_ORIENTATIONAL__        0x6000000000000000
#define __ROTATION_ANGLE__                  0x6000000000000001
#define __ANGULAR_VELOCITY__                0x6000000000000002
#define __GRAVITATIONAL_ACCELERATION__      0x6000000000000003
#define __LINEAR_ACCELERATION__             0x6000000000000004
#define __LINEAR_VELOCITY__                 0x6000000000000005
#define __LINEAR_DISPLACEMENT__             0x6000000000000006
#define __MAGNETISM__                       0x6000000000000007
#define __LATITUDE__                        0x6000000000000008
#define __LONGTITUDE__                      0x6000000000000009



static inline bool IsCommunicationProtocol(uint64_t definition) {
    return (definition & __COMMMUNICATION_PROTOCOLS__) == __COMMMUNICATION_PROTOCOLS__; 
}

static inline bool IsSensorAndInputDevice(uint64_t definition) {
    return (definition & __SENSORS__INPUT_DEVICES__) == __SENSORS__INPUT_DEVICES__;
}

static inline bool IsOutputDevice(uint64_t definition) {
    return (definition & __OUTPUT_DEVICE__) == __OUTPUT_DEVICE__;
}

static inline bool IsDataTypeNonOrientational(uint64_t definition) {
    return (definition & __DATA_TYPES_NON_ORIENTATIONAL__) == __DATA_TYPES_NON_ORIENTATIONAL__;
}

static inline bool IsDataTypeOrientational(uint64_t definition) {
    return (definition & __DATA_TYPES_ORIENTATIONAL__) == __DATA_TYPES_ORIENTATIONAL__;
}

static inline bool IsDataType(uint64_t definition) {
    return IsDataTypeNonOrientational(definition) || IsDataTypeOrientational(definition);
}

static inline uint8_t GetAxis(uint64_t definition) {
    if ((definition & __X_AXIS__) == __X_AXIS__)
        return __X_AXIS__;
    else if ((definition & __Y_AXIS__) == __Y_AXIS__)
        return __Y_AXIS__;
    else if ((definition & __Z_AXIS__) == __Z_AXIS__)
        return __Z_AXIS__;
    else
        return (uint8_t)NAN;
}

static inline uint64_t GetDataTypeWithoutAxis(uint64_t definition) {
    return definition - GetAxis(definition);
}