#ifdef ARDUINO
    #include <Arduino.h>
#endif

#include "Orion/Orion.hpp"
#include "Orion/Sensors/Sensor.hpp"
#include "Orion/Sensors/GPS/GPS.hpp"

static uint64_t DataTypes[] = {
    __LONGITUDE__,
    __LATITUDE__,
    __LINEAR_DISPLACEMENT__
};
static uint64_t DataTypesSize = 3;

uint64_t* Orion::Sensors::GPS::GPS::GetDataTypes() {
    return DataTypes;
}
uint64_t Orion::Sensors::GPS::GPS::GetDataTypesSize() {
    return DataTypesSize;
}


Orion::Sensors::GPS::GPS::GPS() {
    this->_coordinates._longitude = NAN;
    this->_coordinates._latitude = NAN;
    this->_coordinates._altitude = NAN;
}


float Orion::Sensors::GPS::GPS::GetDataType(uint64_t dataType) {
    if (dataType == __LONGITUDE__)
        return this->_coordinates._longitude;
    else if (dataType == __LATITUDE__)
        return this->_coordinates._latitude;
    else if (dataType == __ALTITUDE__)
        return this->_coordinates._altitude;
    else
        return NAN;
}

void Orion::Sensors::GPS::GPS::Update() {
#ifdef ARDUINO
    this->_lastUpdateTime = millis();
#endif
}

bool Orion::Sensors::GPS::GPS::Send(uint8_t* message, uint64_t len) {
    return false;
}

uint64_t Orion::Sensors::GPS::GPS::Receive(uint8_t* message, uint64_t len) {
    return 0;
}

void Orion::Sensors::GPS::GPS::Sleep() {

}

void Orion::Sensors::GPS::GPS::WakeUp() {

}

void Orion::Sensors::GPS::GPS::Reset() {

}


Orion::Sensors::GPS::GPS::~GPS() {
}