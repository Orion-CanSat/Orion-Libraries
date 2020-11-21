#include "Utilities/Memory/Buffer.hpp"

#include <stdio.h>
#include <string.h>

using namespace Orion::Utilities::Memory;

static char* ulltoa(uint64_t num)
{
    char* c = new char[22];
    memset(c, 0, 22);
    snprintf(c, 21, "%" PRIu64, num);
    return c;
}
static char* lltoa(int64_t num)
{
    char* c = new char[22];
    memset(c, 0, 22);
    snprintf(c, 21, "%" PRId64, num);
    return c;
}

Buffer::Buffer(const char* fname, uint32_t size)
{
    _cache = new uint8_t[_size + 1];
    memset(_cache, 0, _size + 1);
    _size = size;
    _used = 0;

    #ifdef ARDUINO
        fptr = SD.open(fname);
    #else
        fptr = fopen(fname, "wb");
    #endif
}

void Buffer::operator<<(int8_t vl)
{
    char* temp = lltoa(vl);
    operator<<(temp);
    delete temp;
}
void Buffer::operator<<(uint8_t vl)
{
    char* temp = ulltoa(vl);
    operator<<(temp);
    delete temp;
}
void Buffer::operator<<(int16_t vl)
{
    char* temp = lltoa(vl);
    operator<<(temp);
    delete temp;
}
void Buffer::operator<<(uint16_t vl)
{
    char* temp = ulltoa(vl);
    operator<<(temp);
    delete temp;
}
void Buffer::operator<<(int32_t vl)
{
    char* temp = lltoa(vl);
    operator<<(temp);
    delete temp;
}
void Buffer::operator<<(uint32_t vl)
{
    char* temp = ulltoa(vl);
    operator<<(temp);
    delete temp;
}
void Buffer::operator<<(int64_t vl)
{
    char* temp = lltoa(vl);
    operator<<(temp);
    delete temp;
}
void Buffer::operator<<(uint64_t vl)
{
    char* temp = ulltoa(vl);
    operator<<(temp);
    delete temp;
}
#ifdef ARDUINO
    void Buffer::operator<<(String vl)
    {
        operator<<(vl.c_str());
    }
#else
    void Buffer::operator<<(std::string vl)
    {
        operator<<(vl.c_str());
    }
#endif
void Buffer::operator<<(const char* vl)
{
    uint32_t sizeOfVl = strlen(vl);
    if (_used + sizeOfVl <= _size)
    {
        memcpy(_cache + _used, vl, sizeOfVl);
        _used += sizeOfVl;
        _cache[_used] = 0x00;
    }
    else
    {
        uint32_t bytesRead = 0;
        memcpy(_cache + _used, vl, (_size - _used));
        bytesRead = _size - _used;
        Flush();

        vl += bytesRead;
        sizeOfVl -= bytesRead;

        bytesRead = 0;
        uint32_t iterations = sizeOfVl / _size;
        for (uint32_t i = 0; i < iterations; i++)
        {
            memcpy(_cache, vl + i * _size, _size);
            Flush();
        }
        memcpy(_cache, vl + iterations * _size, sizeOfVl % _size);
        _used = sizeOfVl % _size;
        _cache[_used] = 0x00;
    }
}

void Buffer::Flush()
{
    #ifdef ARDUINO
        uint32_t size = strlen((const char*)_cache);
        fptr.write(_cache, size);
    #else
        fprintf(fptr, "%s", _cache);
    #endif
}

void Buffer::Clear()
{
    _cache[0] = 0x00;
    _used = 0;
}

Buffer::~Buffer()
{
    if (_used)
        Flush();
    delete _cache;
}