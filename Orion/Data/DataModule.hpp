#ifndef __ORION_DATA_DATAMODULE_H__
#define __ORION_DATA_DATAMODULE_H__

#include "Orion.h"
#include "Orion/Modules/Module.hpp"
#include "Orion/Utilities/Memory/shared_ptr.hpp"

#include <stdint.h>
#include <stdlib.h>

namespace Orion
{
    namespace Data
    {
        template<typename T, uint32_t Y>
        class DataModule
        {
            protected:
                T* _module;

            public:
                DataModule(T* module) { _module = module; }
                
                uint32_t GetType() { return Y; }
                virtual decPlace Get() { return _module->GetData(Y); };

                ~DataModule() { free(_module); }
        };
    }
}

#define GENERATE_DATA(namePascal, type)                                                             \
namespace Orion                                                                                     \
{                                                                                                   \
    namespace Data                                                                                  \
    {                                                                                               \
        template<typename T>                                                                        \
        class namePascal : public DataModule<T, type>                                               \
        {                                                                                           \
            public:                                                                                 \
                namePascal () : DataModule<T, type>(nullptr) { }                                    \
                namePascal (T* module) : DataModule<T, type>(module) { }                            \
        };                                                                                          \
    }                                                                                               \
}                                                                                                   \

#endif//__ORION_DATA_DATAMODULE_H__