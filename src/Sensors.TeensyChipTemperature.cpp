#ifdef ARDUINO
    #include <Arduino.h>
#endif

#include "Orion/Orion.hpp"
#include "Orion/Sensors/TeensyChipTemperature.hpp"
#include "Orion/Sensors/Sensor.hpp"

static uint64_t DataTypes[] = {
    __TEMPERATURE__
};
static uint64_t DataTypesSize = 1;

uint64_t* Orion::Sensors::TeensyChipTemperature::GetDataTypes() {
    return DataTypes;
}
uint64_t Orion::Sensors::TeensyChipTemperature::GetDataTypesSize() {
    return DataTypesSize;
}


extern float tempmonGetTemp();


Orion::Sensors::TeensyChipTemperature::TeensyChipTemperature(uint8_t analogResolution) {
    if (analogResolution != 10 && analogResolution != 16)
        return;

    this->_analogResolution = analogResolution;
    this->_initialized = true;
}


float Orion::Sensors::TeensyChipTemperature::GetDataType(uint64_t dataType) {
    if (dataType == __TEMPERATURE__)
        return this->_temperature;
    else
        return NAN;
}

void Orion::Sensors::TeensyChipTemperature::Update() {
    if (!this->_initialized || (this->_state != __WAKE__))
        return;

#if defined(__TEENSY_3_0__) || defined(__TEENSY_3_1__) || defined(__TEENSY_3_2__) || defined(__TEENSY_3_5__) || defined(__TEENSY_3_6__)
    this->_temperature = (this->_analogResolution == 10) ? (-1.8626 * analogRead(70) + 434.5) : (-0.0293 * analogRead(70) + 440.5);
#elif defined(__TEENSY_4_0__) || defined(__TEENSY_4_1__)
    this->_temperature = tempmonGetTemp();
#endif

#ifdef ARDUINO
    this->_lastUpdateTime = millis();
#endif
}

bool Orion::Sensors::TeensyChipTemperature::Send(uint8_t* message, uint64_t len) {
    return false;
}

uint64_t Orion::Sensors::TeensyChipTemperature::Receive(uint8_t* message, uint64_t len) {
    return 0;
}

void Orion::Sensors::TeensyChipTemperature::Sleep() {
    this->_state = __SLEEP__;
}

void Orion::Sensors::TeensyChipTemperature::WakeUp() {
    this->_state = __WAKE__;
}

void Orion::Sensors::TeensyChipTemperature::Reset() {

}

Orion::Sensors::TeensyChipTemperature::~TeensyChipTemperature() {

}