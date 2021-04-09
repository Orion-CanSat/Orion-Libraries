#pragma once

#include "Orion/Orion.hpp"

namespace Orion {
    namespace Sensors {
        class Sensor {
            protected:
                bool _initialized = false;
                uint8_t _state = __WAKE__;
                uint64_t _type = 0x00;
                uint32_t _lastUpdateTime = 0;

                virtual uint64_t* GetDataTypes();
                virtual uint64_t GetDataTypesSize();
            public:
                Sensor();

                INLINE bool IsInitialized() { return this->_initialized; }

                INLINE uint64_t GetType() { return this->_type; }

                bool HasDataType(uint64_t dataType);
                virtual float GetDataType(uint64_t dataType);

                virtual void Update();
                INLINE uint32_t GetLastUpdateTime() { return this->_lastUpdateTime; }

                virtual bool Send(uint8_t* message, uint64_t len);
                virtual uint64_t Receive(uint8_t* message, uint64_t len);

                virtual void Sleep();
                virtual void WakeUp();

                virtual void Reset();

                ~Sensor();
        };
    }
}