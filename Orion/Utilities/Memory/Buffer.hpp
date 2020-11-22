#ifndef __ORION_UTILITIES_MEMORY_BUFFER_H__
#define __ORION_UTILITIES_MEMORY_BUFFER_H__

#include "Orion.h"

#include <stdint.h>
#ifdef ARDUINO
    #include <WString.h>
#else
    #include <string>
#endif

#include "Orion/Utilities/Memory/unique_ptr.hpp"

namespace Orion
{
    namespace Utilities
    {
        namespace Memory
        {
            class Buffer
            {
                protected:
                    uint8_t* _cache;
                    uint32_t _size;
                    uint32_t _used;

                    bool Initialize();
                public:
                    Buffer();
                    Buffer(uint32_t size);

                    Buffer operator<<(int8_t vl);
                    Buffer operator<<(uint8_t vl);
                    Buffer operator<<(int16_t vl);
                    Buffer operator<<(uint16_t vl);
                    Buffer operator<<(int32_t vl);
                    Buffer operator<<(uint32_t vl);
                    Buffer operator<<(int64_t vl);
                    Buffer operator<<(uint64_t vl);
                    Buffer operator<<(char vl);
                    #ifdef ARDUINO
                        Buffer operator<<(String vl);
                    #else
                        Buffer operator<<(std::string vl);
                    #endif
                    Buffer operator<<(const char* vl);

                    virtual void Flush();
                    void Clear();

                    virtual ~Buffer();
            };
        }
    }
}

#endif//__ORION_UTILITIES_MEMORY_BUFFER_H__