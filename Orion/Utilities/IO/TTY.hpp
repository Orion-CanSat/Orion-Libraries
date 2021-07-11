#ifndef __ORION_UTILITIES_IO_TTY_H__
#define __ORION_UTILITIES_IO_TTY_H__

#include "Orion/Orion.hpp"
#include "Orion/Utilities/IO/IO.hpp"

#include <stdint.h>

namespace Orion
{
    namespace Utilities
    {
        namespace IO
        {
            enum ColorsIndex {
                Black = 0,
                Red = 1,
                Green = 2,
                Yellow = 3,
                Blue = 4,
                Magenta = 5,
                Cyan = 6,
                White = 7,
                BrightBlack = 8,
                BrightRed = 9,
                BrightGreen = 10,
                BrightYellow = 11,
                BrightBlue = 12,
                BrightMagenta = 13,
                BrightCyan = 14,
                BrightWhite = 15
            };

            extern const char* FGColors[16];
            extern const char* BGColors[16];

            extern const char* endl;
            extern const char* ResetTTY;

            class TTY: virtual public Orion::Utilities::IO::IO {
                public:
                    /**
                     * @brief Construct a new TTY object
                     * 
                     */
                    TTY();

                    /**
                     * @brief Construct a new TTY object with a specified buffer size
                     * 
                     * @param size Size of the buffer
                     */
                    TTY(uint32_t size);

                    void Flush();

                    ~TTY();
            };
        }
    }
}

extern Orion::Utilities::IO::TTY orionout;


#endif//__ORION_UTILITIES_IO_TTY_H__