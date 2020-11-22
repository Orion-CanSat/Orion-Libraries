#ifndef __ORION_UTILITIES_LOGGER_CONSOLELOGGER_H__
#define __ORION_UTILITIES_LOGGER_CONSOLELOGGER_H__

#include "Orion.h"

#include "Orion/Utilities/Colors/Colors.hpp"
#include "Orion/Utilities/Memory/Buffer.hpp"

#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include <usb_serial.h>

namespace Orion
{
    namespace Utilities
    {
        namespace Logger
        {
            class ConsoleLogger : public Memory::Buffer
            {
                private:
                    void* _serial;
                    int _type;
                    Colors::Color _bg = (Colors::Color)(-1);
                    Colors::Color _fg = (Colors::Color)(-1);
                    char* _customColor = new char[10];

                    void ChangeCustomColor();

                public:
                    ConsoleLogger(usb_serial_class serial, uint32_t size);
                    ConsoleLogger(HardwareSerial serial, uint32_t size);
                    ConsoleLogger(SoftwareSerial serial, uint32_t size);

                    void SetBackgroundColor(Colors::Color color);
                    void SetForegroundColor(Colors::Color color);
                    Colors::Color GetBackgroundColor();
                    Colors::Color GetForegroundColor();

                    Memory::Buffer operator<<(const char* vl);
                    
                    void Flush();

                    ~ConsoleLogger();
            };
        }
    }
}

#endif//__ORION_UTILITIES_LOGGER_CONSOLELOGGER_H__