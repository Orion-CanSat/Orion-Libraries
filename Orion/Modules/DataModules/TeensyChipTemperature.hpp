#ifndef __ORION_MODULES_DATAMODULES_TEENSYCHIPTEMPERATURE_H__
#define __ORION_MODULES_DATAMODULES_TEENSYCHIPTEMPERATURE_H__

#include "Orion.h"
#include "Orion/Modules/Module.hpp"

namespace Orion
{
    namespace Modules
    {
        namespace DataModules
        {
            class TeensyChipTemperature : virtual public Module
            {
                private:
                    uint8_t _analogResolution;
                    decPlace _temperature = NAN;

                public:
                    TeensyChipTemperature(uint8_t analogResolution = 10);

                    bool HasDataType(uint32_t type);
                    decPlace GetData(uint32_t type);
                    void Update();

                    ~TeensyChipTemperature();
            };
        }
    }
}

#endif//__ORION_MODULES_DATAMODULES_TEENSYCHIPTEMPERATURE_H__