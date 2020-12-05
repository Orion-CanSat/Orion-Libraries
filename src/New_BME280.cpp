#include "Orion/Modules/DataModules/New_BME280.hpp"

using namespace Orion::Modules::DataModules;

static uint8_t SPITransfer(uint8_t val, int8_t sck = -1, int8_t mosi = -1, int8_t miso = -1, SPIClass* spi = nullptr)
{
    uint8_t returnVal = 0;

    if (sck == -1)
        returnVal = spi->transfer(val);
    else for (int8_t i = 7; i >= 0; i--)
    {
        returnVal = returnVal << 1;
        digitalWriteFast(sck, LOW);
        digitalWriteFast(mosi, val & (1 << i));
        digitalWriteFast(sck, HIGH);
        if (digitalReadFast(miso))
            returnVal = returnVal | 1;
    }

    return returnVal;
}


void New_BME280::write1ByteToRegister(uint8_t reg, uint8_t val)
{
    if (this->_wire)
    {
        this->_wire->beginTransmission(this->_i2c);
        this->_wire->write(reg);
        this->_wire->write(val);
        this->_wire->endTransmission();
    }
    else
    {
        if (this->_sck == -1)
            this->_spi->beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
        digitalWriteFast(this->_cs, LOW);
        SPITransfer(reg & ~0x80, this->_sck, this->_mosi, this->_miso, this->_spi);
        SPITransfer(val, this->_sck, this->_mosi, this->_miso, this->_spi);
        digitalWriteFast(this->_cs, HIGH);
        if (this->_sck == -1)
            this->_spi->endTransaction();
    }
}
uint8_t New_BME280::read1ByteFromRegister(uint8_t reg)
{
    uint8_t returnVal = 0;

    if (this->_wire)
    {
        this->_wire->beginTransmission(this->_i2c);
        this->_wire->write(reg);
        this->_wire->endTransmission();
        this->_wire->requestFrom(this->_i2c, 1);
        returnVal = this->_wire->read();
    }
    else
    {
        if (this->_sck == -1)
            this->_spi->beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
        digitalWriteFast(this->_cs, LOW);
        SPITransfer(reg | 0x80, this->_sck, this->_mosi, this->_miso, this->_spi);
        returnVal = SPITransfer(0, this->_sck, this->_mosi, this->_miso, this->_spi);
        digitalWriteFast(this->_cs, HIGH);
        if (this->_sck == -1)
            this->_spi->endTransaction();
    }

    return returnVal;
}
uint16_t New_BME280::read2BytesFromRegister(uint8_t reg)
{
    uint16_t returnVal = 0;

    if (this->_wire)
    {
        this->_wire->beginTransmission(this->_i2c);
        this->_wire->write(reg);
        this->_wire->endTransmission();
        this->_wire->requestFrom(this->_i2c, 2);
        for (int8_t i = 1; i >= 0; i--)
            returnVal = returnVal | this->_wire->read() << i * 8;
    }
    else
    {
        if (this->_sck == -1)
            this->_spi->beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
        digitalWriteFast(this->_cs, LOW);
        SPITransfer(reg | 0x80, this->_sck, this->_mosi, this->_miso, this->_spi);
        returnVal = SPITransfer(0, this->_sck, this->_mosi, this->_miso, this->_spi) << 8;
        returnVal = returnVal | SPITransfer(0, this->_sck, this->_mosi, this->_miso, this->_spi);
        digitalWriteFast(this->_cs, HIGH);
        if (this->_sck == -1)
            this->_spi->endTransaction();
    }

    return returnVal;
}
uint32_t New_BME280::read3BytesFromRegister(uint8_t reg)
{
    uint32_t returnVal = 0;

    if (this->_wire)
    {
        this->_wire->beginTransmission(this->_i2c);
        this->_wire->write(reg);
        this->_wire->endTransmission();
        this->_wire->requestFrom(this->_i2c, 3);
        for (int8_t i = 2; i >= 0; i--)
            returnVal = returnVal | this->_wire->read() << i * 8;
    }
    else
    {
        if (this->_sck == -1)
            this->_spi->beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
        digitalWriteFast(this->_cs, LOW);
        SPITransfer(reg | 0x80, this->_sck, this->_mosi, this->_miso, this->_spi);
        returnVal = SPITransfer(0, this->_sck, this->_mosi, this->_miso, this->_spi) << 16;
        returnVal = returnVal | SPITransfer(0, this->_sck, this->_mosi, this->_miso, this->_spi) << 8;
        returnVal = returnVal | SPITransfer(0, this->_sck, this->_mosi, this->_miso, this->_spi);
        digitalWriteFast(this->_cs, HIGH);
        if (this->_sck == -1)
            this->_spi->endTransaction();
    }

    return returnVal;
}


bool New_BME280::Initialize()
{
    bool returnVal = false;

    if (this->_i2c)
        this->_wire->begin();
    else
    {
        pinMode(this->_cs, OUTPUT);
        digitalWriteFast(this->_cs, HIGH);

        if (this->_sck == -1)
            this->_spi->begin();
        else
        {
            pinMode(this->_sck, OUTPUT);
            pinMode(this->_miso, OUTPUT);
            pinMode(this->_mosi, OUTPUT);
        }
    }

    if (read1ByteFromRegister(0xD0) != 0x60)
        return returnVal;
    
    delay(10);
    write1ByteToRegister(0xE0, 0xB6);
    delay(10);

    returnVal = true;

    return true;
}


bool New_BME280::ReadTemperature()
{
    return true;
}
bool New_BME280::ReadHumidity()
{
    
    return true;
}
bool New_BME280::ReadPressure()
{
    
    return true;
}
bool New_BME280::ReadAltitude()
{
    
    return true;
}


New_BME280::New_BME280(TwoWire* wire)
{
    this->_wire = new TwoWire(*wire);
    this->_i2c = 0x77;

    this->Initialize();
}
New_BME280::New_BME280(TwoWire* wire, bool altI2C)
{
    this->_wire = new TwoWire(*wire);
    this->_i2c = (!altI2C) ? 0x77 : 0x76;

    this->Initialize();
}
New_BME280::New_BME280(int8_t cs, SPIClass* spi)
{
    this->_cs = cs;
    this->_spi = new SPIClass(*spi);

    this->Initialize();
}
New_BME280::New_BME280(int8_t cs, int8_t miso, int8_t mosi, int8_t sck)
{
    this->_cs = cs;
    this->_miso = miso;
    this->_mosi = mosi;
    this->_sck = sck;

    this->Initialize();
}


bool New_BME280::HasDataType(uint32_t type)
{
    switch (type)
    {
        case __TEMPERATURE__:
        case __HUMIDITY__:
        case __PRESSURE__:
        case __ALTITUDE__:
            return true;
        default:
            return false;
    }
}
decPlace New_BME280::GetData(uint32_t type)
{
    switch (type)
    {
        case __TEMPERATURE__:
            return _temperature;
        case __HUMIDITY__:
            return _humidity;
        case __PRESSURE__:
            return _pressure;
        case __ALTITUDE__:
            return _altitude;
        default:
            return NAN;
    }
}
void New_BME280::Update()
{
    ReadTemperature();
    ReadHumidity();
    ReadPressure();
    ReadAltitude();

    _timeOfLastUpdate = millis();
}


New_BME280::~New_BME280()
{
    if (_wire)
        delete _wire;
    else
        delete _spi;
}