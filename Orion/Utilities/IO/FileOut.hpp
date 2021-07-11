#ifndef __ORION_UTILITIES_IO_FILEOUT_H__
#define __ORION_UTILITIES_IO_FILEOUT_H__

#include "Orion/Orion.hpp"
#include "Orion/Utilities/IO/IO.hpp"

#include <stdint.h>

#include <SD.h>

namespace Orion
{
    namespace Utilities
    {
        namespace IO
        {
            class FileOut: virtual public Orion::Utilities::IO::IO {
                private:
                    File _file;

                public:
                    /**
                     * @brief Construct a new File object
                     * 
                     */
                    FileOut(const char* fname);

                    /**
                     * @brief Construct a new File object with a specified buffer size
                     * 
                     * @param size Size of the buffer
                     */
                    FileOut(const char* fname, uint32_t size);

                    void Flush();

                    ~FileOut();
            };
        }
    }
}


#endif//__ORION_UTILITIES_IO_FILEOUT_H__