#ifndef __ORION_UTILITIES_MEMORY_FILE_BLOB_H__
#define __ORION_UTILITIES_MEMORY_FILE_BLOB_H__

#include "Orion.h"

#include <SD.h>

#include <stdint.h>

namespace Orion
{
    namespace Utilities
    {
        namespace Memory
        {
            class FileBlob
            {
                private:
                    uint16_t _cs = -1, _size;
                    File _file;
                    uint16_t _position;
                    uint8_t* _cached = nullptr;
                    uint16_t _cachedSize = 0, _cachedSkip = 0;

                public:
                    FileBlob(int16_t sdCS, uint16_t size);

                    uint8_t& operator[](uint16_t position);

                    void Save();
                    bool Cache(uint16_t skip, uint16_t size);
                    void Release();

                    ~FileBlob();
            };
        }
    }
}

#endif//__ORION_UTILITIES_MEMORY_FILE_BLOB_H__