#ifndef __ORION_DATA_DATAMODULE_H__
#define __ORION_DATA_DATAMODULE_H__

#include "Orion.h"
#include "Orion/Modules/Module.hpp"
#include "Orion/Utilities/Memory/weak_ptr.hpp"

#include <stdint.h>

namespace Orion
{
    namespace Data
    {
        template<uint32_t Y>
        class DataModule
        {
            protected:
                Orion::Utilities::Memory::weak_ptr<Orion::Modules::Module> _module;

            public:
                DataModule(Orion::Modules::Module* module) { _module = Orion::Utilities::Memory::weak_ptr<Orion::Modules::Module>(module); }
                DataModule(Orion::Utilities::Memory::weak_ptr<Orion::Modules::Module> module) { _module = module; }
                
                uint32_t GetType() { return Y; }
                virtual decPlace Get() { return (*(this->_module)).GetData(Y); };

                ~DataModule() { }
        };
    }
}

#define GENERATE_DATA(namePascal, type)                                                                                         \
namespace Orion                                                                                                                 \
{                                                                                                                               \
    namespace Data                                                                                                              \
    {                                                                                                                           \
        class namePascal : public DataModule<type>                                                                              \
        {                                                                                                                       \
            public:                                                                                                             \
                namePascal () : DataModule<type>(nullptr) { }                                                                   \
                namePascal (Orion::Modules::Module* module) : DataModule<type>(module) { }                                      \
                namePascal (Orion::Utilities::Memory::weak_ptr<Orion::Modules::Module> module) : DataModule<type>(module) { }   \
        };                                                                                                                      \
    }                                                                                                                           \
}

#endif//__ORION_DATA_DATAMODULE_H__