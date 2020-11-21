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

                    void operator<<(int8_t vl);
                    void operator<<(uint8_t vl);
                    void operator<<(int16_t vl);
                    void operator<<(uint16_t vl);
                    void operator<<(int32_t vl);
                    void operator<<(uint32_t vl);
                    void operator<<(int64_t vl);
                    void operator<<(uint64_t vl);
                    #ifdef ARDUINO
                        void operator<<(String vl);
                    #else
                        void operator<<(std::string vl);
                    #endif
                    void operator<<(const char* vl);

                    virtual void Flush();
                    void Clear();

                    ~Buffer();
            };
        }
    }
}

#endif//__ORION_UTILITIES_MEMORY_BUFFER_H__