#pragma once

#include "Orion/Orion.h"
#include "Orion/Sensors/Sensor.hpp"

namespace Orion {
    namespace Sensors {
        class BNO055 : public Sensor {
            protected:
                void* _adafruitSensor = NULL;
                int16_t _specialPin = -1;

                float _rotationAngle[3] = { NAN, NAN, NAN };
                float _angularVelocity[3] = { NAN, NAN, NAN };
                float _gravitationalAcceleration[3] = { NAN, NAN, NAN };
                float _linearAcceleration[3] = { NAN, NAN, NAN };
                float _magnetism[3] = { NAN, NAN, NAN };

                float _fixedLinearAcceleration[3] = { NAN, NAN, NAN };
                float _fixedLinearVelocity[3] = { NAN, NAN, NAN };
                float _fixedDisplacement[3] = { NAN, NAN, NAN };

                virtual uint64_t* GetDataTypes();
                virtual uint64_t GetDataTypesSize();
            public:
                BNO055(uint64_t communicationProtocol, int16_t specialPin = -1);

                virtual float GetDataType(uint64_t dataType);

                virtual void Update();

                virtual bool Send(uint8_t* message, uint64_t len);
                virtual uint64_t Receive(uint8_t* message, uint64_t len);

                virtual void Sleep();
                virtual void WakeUp();

                virtual void Reset();

                ~BNO055();
        };
    }
}