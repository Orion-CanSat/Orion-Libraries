#include <Arduino.h>
#include "Orion/Modules/DataModules/TeensyChipTemperature.hpp"

extern float tempmonGetTemp(void);

using namespace Orion::Modules::DataModules;

TeensyChipTemperature::TeensyChipTemperature(uint8_t analogResolution)
{
    if (analogResolution != 10 && analogResolution != 16)
        return;
    this->_analogResolution = analogResolution;
    this->_initialized = true;
}

bool TeensyChipTemperature::HasDataType(uint32_t type)
{
    return (type == __TEMPERATURE__);
}

decPlace TeensyChipTemperature::GetData(uint32_t type)
{
    return (type == __TEMPERATURE__) ? this->_temperature : NAN;
}

void TeensyChipTemperature::Update()
{
    if (!this->_initialized)
        return;

    #if   (defined(__TEENSY_3_0__) || defined(__TEENSY_3_1__) || defined(__TEENSY_3_2__) || defined(__TEENSY_3_5__) || defined(__TEENSY_3_6__))
        this->_temperature =  (this->_analogResolution == 10) ? (-1.8626 * analogRead(70) + 434.5) : (-0.0293 * analogRead(70) + 440.5);
    #elif (defined(__TEENSY_4_0__) || defined(__TEENSY_4_1__))
        this->_temperature =  tempmonGetTemp();
    #endif

    _timeOfLastUpdate = millis();
}

TeensyChipTemperature::~TeensyChipTemperature()
{
    _initialized = false;
    delete _devicePtr;
}