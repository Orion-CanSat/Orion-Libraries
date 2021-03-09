#ifdef ARDUINO
    #include <Arduino.h>
#endif

#include "Orion/Orion.hpp"
#include "Orion/Sensors/Sensor.hpp"


uint64_t* Orion::Sensors::Sensor::GetDataTypes() {
    return (uint64_t*)NULL;
}
uint64_t Orion::Sensors::Sensor::GetDataTypesSize() {
    return 0;
}


Orion::Sensors::Sensor::Sensor() {

}


bool Orion::Sensors::Sensor::HasDataType(uint64_t dataType) {
    uint64_t* dataTypes = this->GetDataTypes();
    uint64_t dataTypesSize = this->GetDataTypesSize();

    for (uint64_t i = 0; i < dataTypesSize; i++) {
        if (dataTypes[i] == dataType)
            return true;
    }
    return false;
}

float Orion::Sensors::Sensor::GetDataType(uint64_t dataType) {
    return NAN;
}


void Orion::Sensors::Sensor::Update() {
#ifdef ARDUINO
    this->_lastUpdateTime = millis();
#endif
}

bool Orion::Sensors::Sensor::Send(uint8_t* message, uint64_t len) {
    return false;
}

uint64_t Orion::Sensors::Sensor::Receive(uint8_t* message, uint64_t len) {
    return 0;
}

void Orion::Sensors::Sensor::Sleep() {
    this->_state = __SLEEP__;
}
void Orion::Sensors::Sensor::WakeUp() {
    this->_state = __WAKE__;
}

void Orion::Sensors::Sensor::Reset() {

}

Orion::Sensors::Sensor::~Sensor() {

}