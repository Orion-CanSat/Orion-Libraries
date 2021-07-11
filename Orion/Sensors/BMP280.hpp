#pragma once

#include "Orion/Orion.hpp"
#include "Orion/Sensors/Sensor.hpp"

namespace Orion {
    namespace Sensors {
        class BMP280 : public Sensor {
            protected:
                void* _adafruitSensor = NULL;
                int16_t _specialPin = -1;
                int16_t _MOSI = -1;
                int16_t _MISO = -1;
                int16_t _SCK = -1;

                float _temperature = NAN;
                float _pressure = NAN;
                float _altitude = NAN;

                virtual uint64_t* GetDataTypes();
                virtual uint64_t GetDataTypesSize();
            public:
                BMP280(uint64_t communicationProtocol, int16_t specialPin = -1, int16_t MOSI = -1, int16_t MISO = -1, int16_t SCK = -1);

                virtual float GetDataType(uint64_t dataType);

                virtual void Update();

                virtual bool Send(uint8_t* message, uint64_t len);
                virtual uint64_t Receive(uint8_t* message, uint64_t len);

                virtual void Sleep();
                virtual void WakeUp();

                virtual void Reset();

                ~BMP280();
        };
    }
}