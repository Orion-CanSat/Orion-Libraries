#include "Utilities/Memory/FileBlob.hpp"

#include <string>

using namespace Orion::Utilities::Memory;

bool Initialized = false;

std::string RandomString(const int len)
{    
    std::string s;
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    
    randomSeed(analogRead(0));

    for (int i = 0; i < len; ++i) 
        s += alphanum[random(sizeof(alphanum) - 1)];

    return s;
    
}

uint8_t* zero = { 0x00 };

FileBlob::FileBlob(int16_t sdCS, uint16_t size)
{
    _cs = sdCS;
    _size = size;

    SD.begin(sdCS);

    if (Initialized)
        return;

    if (SD.exists(".FileBlob/"))
        SD.rmdir(".FileBlob/");

    Initialized = true;
    _file = SD.open((std::string(".FileBlob/") + RandomString(12)).c_str(), FILE_READ | FILE_WRITE);
    
    for (int i = 0; i < _size; i++)
        _file.write(zero, 1);
}

uint8_t& FileBlob::operator[](uint16_t position)
{
    if (_cachedSkip < position && position < _cachedSkip + _cachedSize)
    {
        Cache(position - 1, _cachedSize);
        return _cached[1];
    }
    else
        return _cached[position - _cachedSkip];
}

void FileBlob::Save()
{
    if (!_cached)
        return;
    
    _file.seek(_cachedSkip);
    _file.write(_cached, _cachedSize);
    
}
bool FileBlob::Cache(uint16_t skip, uint16_t size)
{
    if (size + skip >= _size)
        return false;
    if (!_cached)
    {
        _cached = (uint8_t*)malloc(size * sizeof(uint8_t));
        if (!_cached)
            return false;
    }
    if (size > _cachedSize)
    {
        _cached = (uint8_t*)realloc(_cached, size * sizeof(uint8_t));
        if (!_cached)
            return false;
    }

    _cachedSize = size;
    _cachedSize = skip;

    _file.seek(skip);
    _file.readBytes(_cached, size);
    _file.seek(skip);

    return true;
}
void FileBlob::Release()
{
    if (_cached)
        free(_cached);

    _cachedSize = _cachedSkip = 0;
}

FileBlob::~FileBlob() { _file.close(); }