#ifdef ARDUINO
    #include <Arduino.h>
#endif

#include "Orion/Orion.h"
#include "Orion/Sensors/BNO055.hpp"
#include "Orion/Sensors/Sensor.hpp"

#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

static uint64_t DataTypes[] = {
    __ROTATION_ANGLE__,
    __ANGULAR_VELOCITY__,
    __LINEAR_ACCELERATION__,
    __LINEAR_VELOCITY__,
    __LINEAR_DISPLACEMENT__,
    __MAGNETISM__
};
static uint64_t DataTypesSize = 6;

uint64_t* Orion::Sensors::BNO055::GetDataTypes() {
    return DataTypes;
}
uint64_t Orion::Sensors::BNO055::GetDataTypesSize() {
    return DataTypesSize;
}


Orion::Sensors::BNO055::BNO055(uint64_t communicationProtocol, int16_t specialPin) {
    if(communicationProtocol == __I2C__) {
        if (specialPin >= 0) {
            this->_adafruitSensor = (void*)(new Adafruit_BNO055(specialPin));
        }
        else {
            this->_adafruitSensor = (void*)(new Adafruit_BNO055());
        }
    }
    else {
        this->_initialized = false;
        return;
    }

    this->_initialized = ((Adafruit_BNO055*)(this->_adafruitSensor))->begin();

    if (!this->_initialized) {
        delete ((Adafruit_BNO055*)this->_adafruitSensor);
        this->_adafruitSensor = NULL;
        return;
    }
    if (communicationProtocol == __SPI__ || specialPin >= 0)
        this->_specialPin = specialPin;

    this->_state = __WAKE__;
}


float Orion::Sensors::BNO055::GetDataType(uint64_t dataType) {
    if (dataType == (__ROTATION_ANGLE__ | __X_AXIS__))
        return this->_rotationAngle[0];
    else if (dataType == (__ROTATION_ANGLE__ | __Y_AXIS__))
        return this->_rotationAngle[1];
    else if (dataType == (__ROTATION_ANGLE__ | __Z_AXIS__))
        return this->_rotationAngle[2];
    
    else if (dataType == (__ANGULAR_VELOCITY__ | __X_AXIS__))
        return this->_angularVelocity[0];
    else if (dataType == (__ANGULAR_VELOCITY__ | __Y_AXIS__))
        return this->_angularVelocity[1];
    else if (dataType == (__ANGULAR_VELOCITY__ | __Z_AXIS__))
        return this->_angularVelocity[2];
    
    else if (dataType == (__GRAVITATIONAL_ACCELERATION__ | __X_AXIS__))
        return this->_gravitationalAcceleration[0];
    else if (dataType == (__GRAVITATIONAL_ACCELERATION__ | __Y_AXIS__))
        return this->_gravitationalAcceleration[1];
    else if (dataType == (__GRAVITATIONAL_ACCELERATION__ | __Z_AXIS__))
        return this->_gravitationalAcceleration[2];
    
    else if (dataType == (__LINEAR_ACCELERATION__ | __X_AXIS__))
        return this->_linearAcceleration[0];
    else if (dataType == (__LINEAR_ACCELERATION__ | __Y_AXIS__))
        return this->_linearAcceleration[1];
    else if (dataType == (__LINEAR_ACCELERATION__ | __Z_AXIS__))
        return this->_linearAcceleration[2];

    else if (dataType == (__MAGNETISM__ | __X_AXIS__))
        return this->_magnetism[0];
    else if (dataType == (__MAGNETISM__ | __Y_AXIS__))
        return this->_magnetism[1];
    else if (dataType == (__MAGNETISM__ | __Z_AXIS__))
        return this->_magnetism[2];
    
    else
        return NAN;
}

void Orion::Sensors::BNO055::Update() {
    if (!this->_initialized || !this->_adafruitSensor || (this->_state != __WAKE__))
        return;

    imu::Vector<3> euler = ((Adafruit_BNO055*)(this->_adafruitSensor))->getVector(Adafruit_BNO055::VECTOR_EULER);
    imu::Vector<3> gyroscope = ((Adafruit_BNO055*)(this->_adafruitSensor))->getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    imu::Vector<3> gravity = ((Adafruit_BNO055*)(this->_adafruitSensor))->getVector(Adafruit_BNO055::VECTOR_GRAVITY);
    imu::Vector<3> acceleration = ((Adafruit_BNO055*)(this->_adafruitSensor))->getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    imu::Vector<3> magnetism = ((Adafruit_BNO055*)(this->_adafruitSensor))->getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    
    for (int i = 0; i < 3; i++) {
        this->_rotationAngle[i] = euler[i];
        this->_angularVelocity[i] = gyroscope[i];
        this->_gravitationalAcceleration[i] = gravity[i];
        this->_linearAcceleration[i] = acceleration[i];
        this->_magnetism[i] = magnetism[i];
    }

#ifdef ARDUINO
    this->_lastUpdateTime = millis();
#endif
}

bool Orion::Sensors::BNO055::Send(uint8_t* message, uint64_t len) {
    return false;
}

uint64_t Orion::Sensors::BNO055::Receive(uint8_t* message, uint64_t len) {
    return 0;
}

void Orion::Sensors::BNO055::Sleep() {

}

void Orion::Sensors::BNO055::WakeUp() {

}

void Orion::Sensors::BNO055::Reset() {

}

Orion::Sensors::BNO055::~BNO055() {
    if (this->_initialized && this->_adafruitSensor) {
        delete ((Adafruit_BNO055*)this->_adafruitSensor);
        this->_adafruitSensor = NULL;
    }
}