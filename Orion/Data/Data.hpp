#pragma once

#include <stdint.h>

#include "Orion/Orion.hpp"
#include "Orion/Sensors/Sensor.hpp"

namespace Orion
{
    namespace Data
    {
        class Data
        {
            protected:
                Orion::Sensors::Sensor* _sensor = NULL;
                bool _initialized = false;
                uint64_t _type = 0x00;
            public:
                Data() {

                }

                INLINE bool IsInitialized() { return this->_initialized && this->_sensor->IsInitialized(); }
                
                INLINE uint32_t GetType() { return this->_type; }
                
                INLINE virtual float Get(uint64_t axis = __AXIS__) {
                    if (!this->IsInitialized())
                        return NAN;
                    
                    return this->_sensor->GetDataType(this->_type | axis);
                }

                INLINE virtual bool Bind(Orion::Sensors::Sensor* sensor) {
                    this->_initialized = false;
                    if (!sensor || !sensor->HasDataType(this->_type))
                        return false;

                    this->_sensor = sensor;
                    this->_initialized = true;
                    return true;
                }

                ~Data() {
                    if (this->_sensor) {
                        this->_sensor = NULL;
                    }

                    this->_initialized = false;
                }
        };
    }
}

#define GENERATE_DATA(namePascal, type)                                                                                         \
namespace Orion {                                                                                                               \
    namespace Data {                                                                                                            \
        class namePascal : public Data                                                                                          \
        {                                                                                                                       \
            public:                                                                                                             \
                namePascal (Orion::Sensors::Sensor* sensor) {                                                                   \
                    this->_type = type;                                                                                         \
                    this->Bind(sensor);                                                                                         \
                }                                                                                                               \
        };                                                                                                                      \
    }                                                                                                                           \
}
