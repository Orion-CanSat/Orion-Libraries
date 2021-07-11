#ifdef ARDUINO
    #include <Arduino.h>
#endif

#include "Orion/Orion.hpp"
#include "Orion/Sensors/BMP280.hpp"
#include "Orion/Sensors/Sensor.hpp"

#include <Adafruit_BMP280.h>

static uint64_t DataTypes[] = {
    __TEMPERATURE__,
    __PRESSURE__,
    __ALTITUDE__
};
static uint64_t DataTypesSize = 4;

uint64_t* Orion::Sensors::BMP280::GetDataTypes() {
    return DataTypes;
}
uint64_t Orion::Sensors::BMP280::GetDataTypesSize() {
    return DataTypesSize;
}


Orion::Sensors::BMP280::BMP280(uint64_t communicationProtocol, int16_t specialPin, int16_t MOSI, int16_t MISO, int16_t SCK) {
    if (communicationProtocol == __SPI__) {
        if (specialPin < 0)
            return;
        if ( MOSI < 0 || MISO < 0 || SCK < 0) {
            this->_adafruitSensor = (void*)(new Adafruit_BMP280(specialPin));
        }
        else {
            this->_adafruitSensor = (void*)(new Adafruit_BMP280(specialPin, MOSI, MISO, SCK));
        }
    }
    else if(communicationProtocol == __I2C__) {
        if (specialPin >= 0) {
            this->_adafruitSensor = (void*)(new Adafruit_BMP280(specialPin));
        }
        else {
            this->_adafruitSensor = (void*)(new Adafruit_BMP280());
        }
    }
    else {
        this->_initialized = false;
        return;
    }

    this->_initialized = ((Adafruit_BMP280*)(this->_adafruitSensor))->begin();

    if (!this->_initialized) {
        delete ((Adafruit_BMP280*)this->_adafruitSensor);
        this->_adafruitSensor = NULL;
        return;
    }
    if (communicationProtocol == __SPI__ || specialPin >= 0)
        this->_specialPin = specialPin;
    if ( MOSI >= 0 && MISO >= 0 && SCK >= 0) {
        this->_MOSI = MOSI;
        this->_MISO = MISO;
        this->_SCK = SCK;
    }
}


float Orion::Sensors::BMP280::GetDataType(uint64_t dataType) {
    if (dataType == __TEMPERATURE__)
        return this->_temperature;
    else if (dataType == __PRESSURE__)
        return this->_pressure;
    else if (dataType == __ALTITUDE__)
        return this->_altitude;
    else
        return NAN;
}

void Orion::Sensors::BMP280::Update() {
    if (!this->_initialized || !this->_adafruitSensor || (this->_state != __WAKE__))
        return;

    this->_temperature = ((Adafruit_BMP280*)(this->_adafruitSensor))->readTemperature();
    this->_pressure = ((Adafruit_BMP280*)(this->_adafruitSensor))->readPressure();
    this->_altitude = ((Adafruit_BMP280*)(this->_adafruitSensor))->readAltitude(1013.25);

#ifdef ARDUINO
    this->_lastUpdateTime = millis();
#endif
}

bool Orion::Sensors::BMP280::Send(uint8_t* message, uint64_t len) {
    return false;
}

uint64_t Orion::Sensors::BMP280::Receive(uint8_t* message, uint64_t len) {
    return 0;
}

void Orion::Sensors::BMP280::Sleep() {

}

void Orion::Sensors::BMP280::WakeUp() {

}

void Orion::Sensors::BMP280::Reset() {

}

Orion::Sensors::BMP280::~BMP280() {
    if (this->_initialized && this->_adafruitSensor) {
        delete ((Adafruit_BMP280*)this->_adafruitSensor);
        this->_adafruitSensor = NULL;
    }
}