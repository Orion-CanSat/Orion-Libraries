#pragma once

#include <stdint.h>

#include "Orion/Orion.hpp"
#include "Orion/Sensors/Sensor.hpp"

namespace Orion {
    namespace Sensors {
        class TeensyChipTemperature : public Sensor {
            protected:
                uint8_t _analogResolution;
                float _temperature = NAN;

                virtual uint64_t* GetDataTypes();
                virtual uint64_t GetDataTypesSize();
            public:
                TeensyChipTemperature(uint8_t analogResolution = 10);

                virtual float GetDataType(uint64_t dataType);

                virtual void Update();

                virtual bool Send(uint8_t* message, uint64_t len);
                virtual uint64_t Receive(uint8_t* message, uint64_t len);

                virtual void Sleep();
                virtual void WakeUp();

                virtual void Reset();

                ~TeensyChipTemperature();
        };
    }
}