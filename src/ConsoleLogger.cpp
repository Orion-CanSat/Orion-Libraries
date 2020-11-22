#include "Orion/Utilities/Logger/ConsoleLogger.hpp"

#include <stdio.h>
#include <string.h>

using namespace Orion::Utilities;
using namespace Orion::Utilities::Logger;

void ConsoleLogger::ChangeCustomColor()
{
    snprintf(_customColor,
        10,
        "%c[%d;%dm",
        '\033',
        (((int)_bg <= 30 && (int)_bg <= 37 ) ||
            ((int)_bg <= 90 && (int)_bg <= 97 )) ?
                (int)_bg : 0,
        (((int)_fg <= 340 && (int)_fg <= 47 ) ||
            ((int)_fg <= 100 && (int)_fg <= 107 )) ?
                (int)_fg : 0
    );
}

ConsoleLogger::ConsoleLogger(usb_serial_class serial, uint32_t size)
{
    _size = size;
    _used = 0;
    Initialize();

    _serial = (void*)(new usb_serial_class(serial));
    _type = 0;
    ChangeCustomColor();
}
ConsoleLogger::ConsoleLogger(HardwareSerial serial, uint32_t size)
{
    _size = size;
    _used = 0;
    Initialize();

    _serial = (void*)(new HardwareSerial(serial));
    _type = 1;
    ChangeCustomColor();
}
ConsoleLogger::ConsoleLogger(SoftwareSerial serial, uint32_t size)
{
    _size = size;
    _used = 0;
    Initialize();

    _serial = (void*)(new SoftwareSerial(serial));
    _type = 2;
    ChangeCustomColor();
}

void ConsoleLogger::SetBackgroundColor(Colors::Color color)
{
    _bg = color;
    ChangeCustomColor();
}
void ConsoleLogger::SetForegroundColor(Colors::Color color)
{
    _fg = (Colors::Color)(color + 10);
    ChangeCustomColor();
}

Colors::Color ConsoleLogger::GetBackgroundColor() { return _bg; }
Colors::Color ConsoleLogger::GetForegroundColor() { return ((int)_fg != -1) ? (Colors::Color)(_fg - 10) : (Colors::Color)-1; }

Memory::Buffer ConsoleLogger::operator<<(const char* vl)
{
    return Memory::Buffer::operator<<("\033[0;93m[LOG ").operator<<(millis()).operator<<("]: ").operator<<(_customColor).operator<<(vl).operator<<('\n');
}

void ConsoleLogger::Flush()
{
    if (_type == 0)
        ((usb_serial_class*)_serial)->write(_cache, _used);
    else if (_type == 1)
        ((HardwareSerial*)_serial)->write(_cache, _used);
    else if (_type == 2)
        ((SoftwareSerial*)_serial)->write(_cache, _used);
    
    _cache[0] = 0x00;
    _used = 0;
}

ConsoleLogger::~ConsoleLogger()
{
    if (_used)
        Flush();

    if (_type == 0)
    {
        ((HardwareSerial*)_serial)->end();
        delete ((HardwareSerial*)_serial);
    }
    else if (_type == 1)
    {
        ((HardwareSerial*)_serial)->end();
        delete ((HardwareSerial*)_serial);
    }
    else if (_type == 2)
    {
        ((SoftwareSerial*)_serial)->end();
        delete ((SoftwareSerial*)_serial);
    }
}