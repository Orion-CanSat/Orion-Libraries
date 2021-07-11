#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Arduino.h>

#include <Orion.h>
#include <Orion/Utilities/IO/IO.hpp>
#include <Orion/Utilities/IO/TTY.hpp>

#define DEFAULT_IO_BUFFER_SIZE 1024

Orion::Utilities::IO::TTY::TTY() {
    this->CreateBuffer(DEFAULT_IO_BUFFER_SIZE + 1);
    this->_buffer[this->_sizeOfBuffer] = '\0';
}

Orion::Utilities::IO::TTY::TTY(uint32_t size) {
    this->CreateBuffer(size + 1);
    this->_buffer[this->_sizeOfBuffer] = '\0';
}


void Orion::Utilities::IO::TTY::Flush() {
    if (!this->_buffer)
        return;

    Serial.write(this->_buffer, this->_bytesWritten);
    Serial.flush();
    this->_bytesWritten = 0;
}

Orion::Utilities::IO::TTY::~TTY() {
    if (!this->_buffer)
        free(this->_buffer);
    this->_buffer = NULL;
}

namespace Orion {
    namespace Utilities {
        namespace IO {
            const char* FGColors[16] = {
                "\e[30m",
                "\e[31m",
                "\e[32m",
                "\e[33m",
                "\e[34m",
                "\e[35m",
                "\e[36m",
                "\e[37m",
                "\e[90m",
                "\e[91m",
                "\e[92m",
                "\e[93m",
                "\e[94m",
                "\e[95m",
                "\e[96m",
                "\e[97m"
            };

            const char* BGColors[16] = {
                "\e[40m",
                "\e[41m",
                "\e[42m",
                "\e[43m",
                "\e[44m",
                "\e[45m",
                "\e[46m",
                "\e[47m",
                "\e[100m",
                "\e[101m",
                "\e[102m",
                "\e[103m",
                "\e[104m",
                "\e[105m",
                "\e[106m",
                "\e[107m"
            };

            const char* endl = "\n";
            const char* ResetTTY = "\e[0m";
        }
    }
}


Orion::Utilities::IO::TTY orionout = Orion::Utilities::IO::TTY();