#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Orion.h>
#include <Orion/Utilities/IO/IO.hpp>
#include <Orion/Utilities/IO/FileOut.hpp>

#include <SD.h>

#define DEFAULT_IO_BUFFER_SIZE 1024

Orion::Utilities::IO::FileOut::FileOut(const char* fname) {
    this->CreateBuffer(DEFAULT_IO_BUFFER_SIZE + 1);
    this->_buffer[this->_sizeOfBuffer] = '\0';
    this->_file = SD.open(fname, FILE_WRITE);
}

Orion::Utilities::IO::FileOut::FileOut(const char* fname, uint32_t size) {
    this->CreateBuffer(size + 1);
    this->_buffer[this->_sizeOfBuffer] = '\0';
    this->_file = SD.open(fname, FILE_WRITE);
}

void Orion::Utilities::IO::FileOut::Flush() {
    if (this->_buffer && this->_file) {
        this->_file.write(this->_buffer, this->_bytesWritten);
        this->_file.flush();
    }
    this->_bytesWritten = 0;
}

Orion::Utilities::IO::FileOut::~FileOut() {
    if (!this->_buffer)
        free(this->_buffer);
    this->_buffer = NULL;
    this->_file.close();
}