#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Orion.h>
#include <Orion/Utilities/IO/IO.hpp>

#define NUN_TO_STR(format, val) \
    char strVal[22];    \
    snprintf(strVal, 22 * sizeof(char), "%" format, val)

#define DEFAULT_IO_BUFFER_SIZE 1024

void Orion::Utilities::IO::IO::FlushIfNecessary() {
    if (this->_buffer && (this->_bytesWritten >= this->_sizeOfBuffer))
        this->Flush();
}


bool Orion::Utilities::IO::IO::CreateBuffer(uint32_t size) {
    this->_buffer = (uint8_t*)malloc(size * sizeof(uint8_t));
    if (!this->_buffer)
        return false;
    
    this->_sizeOfBuffer = size - 1;

    memset(this->_buffer, 0, size * sizeof(uint8_t));

    return true;
}



Orion::Utilities::IO::IO::IO() {
    this->CreateBuffer(DEFAULT_IO_BUFFER_SIZE + 1);
    this->_buffer[this->_sizeOfBuffer] = '\0';
}

Orion::Utilities::IO::IO::IO(uint32_t size) {
    this->CreateBuffer(size + 1);
    this->_buffer[this->_sizeOfBuffer] = '\0';
}



void Orion::Utilities::IO::IO::Flush() {
    this->_bytesWritten = 0;
}

Orion::Utilities::IO::IO& Orion::Utilities::IO::IO::operator<<(bool val) {
    return ((*this) << ((val) ? "1" : "0"));
}

Orion::Utilities::IO::IO& Orion::Utilities::IO::IO::operator<<(int8_t val) {
    NUN_TO_STR(PRIi8, val);

    return ((*this) << strVal);
}

Orion::Utilities::IO::IO& Orion::Utilities::IO::IO::operator<<(uint8_t val) {
    NUN_TO_STR(PRIu8, val);

    return ((*this) << strVal);
}

Orion::Utilities::IO::IO& Orion::Utilities::IO::IO::operator<<(int16_t val) {
    NUN_TO_STR(PRIi16, val);

    return ((*this) << strVal);
}

Orion::Utilities::IO::IO& Orion::Utilities::IO::IO::operator<<(uint16_t val) {
    NUN_TO_STR(PRIu16, val);

    return ((*this) << strVal);
}

Orion::Utilities::IO::IO& Orion::Utilities::IO::IO::operator<<(int32_t val) {
    NUN_TO_STR(PRIi32, val);

    return ((*this) << strVal);
}

Orion::Utilities::IO::IO& Orion::Utilities::IO::IO::operator<<(uint32_t val) {
    NUN_TO_STR(PRIu32, val);

    return ((*this) << strVal);
}

Orion::Utilities::IO::IO& Orion::Utilities::IO::IO::operator<<(int64_t val) {
    NUN_TO_STR(PRIi64, val);

    return ((*this) << strVal);
}

Orion::Utilities::IO::IO& Orion::Utilities::IO::IO::operator<<(uint64_t val) {
    NUN_TO_STR(PRIu64, val);

    return ((*this) << strVal);
}

Orion::Utilities::IO::IO& Orion::Utilities::IO::IO::operator<<(float val) {
    NUN_TO_STR("f", val);

    return ((*this) << strVal);
}

Orion::Utilities::IO::IO& Orion::Utilities::IO::IO::operator<<(double val) {
    NUN_TO_STR("lf", val);

    return ((*this) << strVal);
}

Orion::Utilities::IO::IO& Orion::Utilities::IO::IO::operator<<(const char* val) {
    if (!this->_buffer)
        return *this;

    this->FlushIfNecessary();

    uint32_t size = strlen(val);

    // Check if val can fit in the buffer without needing to Flush it
    if (size + this->_bytesWritten < this->_sizeOfBuffer) {
        memcpy(&(this->_buffer[this->_bytesWritten]), val, size * sizeof(const char));
        this->_bytesWritten += size;
    }
    else {
        // Copy values that can fit in the buffer without needing to Flush it
        memcpy(&(this->_buffer[this->_bytesWritten]), val, (this->_sizeOfBuffer - this->_bytesWritten) * sizeof(const char));
        val += (this->_sizeOfBuffer - this->_bytesWritten) * sizeof(const char);
        this->_bytesWritten = this->_sizeOfBuffer + 1;

        // Pass the rest of the val to be put to buffer
        (*this) << val;
    }

    return *this;
}

Orion::Utilities::IO::IO::~IO() {
    if (!this->_buffer)
        free(this->_buffer);
    this->_buffer = NULL;
}