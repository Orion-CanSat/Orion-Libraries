#include "Orion/Utilities/Logger/FileLogger.hpp"

#include <string.h>

using namespace Orion::Utilities;
using namespace Orion::Utilities::Logger;

FileLogger::FileLogger(const char* fname, uint32_t size)
{
    _size = size;
    _used = 0;
    Initialize();
    uint32_t sizeOfFname = strlen(fname);
    _fname = new char[sizeOfFname + 1];
    memcpy((void*)_fname, fname, sizeOfFname + 1);
    #ifdef ARDUINO
        _fptr = SD.open(_fname, FILE_WRITE);
    #else
        _fptr = fopen(_fname, "wb");
    #endif
}

Memory::Buffer FileLogger::operator<<(const char* vl)
{
    return Memory::Buffer::operator<<("[LOG ").operator<<(millis()).operator<<("]: ").operator<<(vl).operator<<('\n');
}

void FileLogger::Flush()
{
    #ifdef ARDUINO
        _fptr.write(_cache, _used);
        _fptr.flush();
    #else
        fwrite(_cache, _used, 1, _fptr);
    #endif

    _cache[0] = 0x00;
    _used = 0;
}

FileLogger::~FileLogger()
{
    #ifdef ARDUINO
        _fptr.close();
    #else
        fclose(_fptr);
    #endif 

    delete _fname;
}