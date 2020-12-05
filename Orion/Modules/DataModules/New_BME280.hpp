#ifndef __ORION_MODULES_DATAMODULES_NEWBME280_H__
#define __ORION_MODULES_DATAMODULES_NEWBME280_H__

#include "Orion.h"
#include "Orion/Modules/Module.hpp"

#include "stdint.h"

#include "Wire.h"
#include "SPI.h"

namespace Orion
{
    namespace Modules
    {
        namespace DataModules
        {
            class New_BME280 : virtual public Module
            {
                protected:
                    int8_t _i2c = -1;
                    int8_t _cs = -1, _miso = -1, _mosi = -1, _sck = -1;
                    decPlace _temperature = NAN, _humidity = NAN, _pressure = NAN, _altitude = NAN;

                    TwoWire* _wire = (TwoWire*)NULL;
                    SPIClass* _spi = (SPIClass*)NULL;

                    void write1ByteToRegister(uint8_t reg, uint8_t val);
                    uint8_t read1ByteFromRegister(uint8_t reg);
                    uint16_t read2BytesFromRegister(uint8_t reg);
                    uint32_t read3BytesFromRegister(uint8_t reg);

                    bool Initialize();

                    bool ReadTemperature();
                    bool ReadHumidity();
                    bool ReadPressure();
                    bool ReadAltitude();

                public:
                    New_BME280(TwoWire* wire = &Wire);
                    New_BME280(TwoWire* wire = &Wire, bool altI2C = false);
                    New_BME280(int8_t cs, SPIClass* spi = &SPI);
                    New_BME280(int8_t cs, int8_t miso, int8_t mosi, int8_t sck);

                    bool HasDataType(uint32_t type);
                    decPlace GetData(uint32_t type);
                    void Update();

                    ~New_BME280();
            };
        }
    }
}

#endif//__ORION_MODULES_DATAMODULES_NEWBME280_H__