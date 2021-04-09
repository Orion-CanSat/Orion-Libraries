#ifdef ARDUINO
    #include <Arduino.h>
    #include <SoftwareSerial.h>

    #include "Orion/Orion.hpp"
    #include "Orion/Sensors/Sensor.hpp"
    #include "Orion/Sensors/GPS/Coordinates.hpp"
    #include "Orion/Sensors/GPS/GPS.hpp"
    #include "Orion/Sensors/GPS/MTK3339.hpp"

    #include <Adafruit_GPS.h>



    Orion::Sensors::GPS::MTK3339::MTK3339(HardwareSerial* serial) {
        this->_type = __GPS__;
        if (serial == NULL)
            return;
        this->_adafruitSensor = new Adafruit_GPS(serial);
        if (this->_adafruitSensor) {
            this->_initialized = true;
            this->_hardwareSerial = serial;
        }

        this->Reset();
    }

    #if (defined(__AVR__) || defined(ESP8266)) && defined(USE_SW_SERIAL)
        Orion::Sensors::GPS::MTK3339::MTK3339(SoftwareSerial* serial) {
            this->_type = __GPS__;
            if (serial == NULL)
                return;
            this->_adafruitSensor = new Adafruit_GPS(serial);
            if (this->_adafruitSensor) {
                this->_initialized = true;
                this->_softwareSerial = serial;
            }

            this->Reset();
        }
    #endif


    void Orion::Sensors::GPS::MTK3339::Update() {
        if (!this->_initialized || !this->_adafruitSensor || (!this->_hardwareSerial
        #if (defined(__AVR__) || defined(ESP8266)) && defined(USE_SW_SERIAL)
            && !this->_softwareSerial
        #endif
        ))
            return;

        uint32_t timeNow = millis();
        for (uint64_t i = 0; i < timeNow - this->_lastUpdateTime; i++)
            ((Adafruit_GPS*)(this->_adafruitSensor))->read();
        
        this->_lastUpdateTime = timeNow;
    }


    bool Orion::Sensors::GPS::MTK3339::Send(uint8_t* message, uint64_t len) {
        return false;
    }

    uint64_t Orion::Sensors::GPS::MTK3339::Receive(uint8_t* message, uint64_t len) {
        return 0;
    }


    void Orion::Sensors::GPS::MTK3339::Sleep() {
        if (!this->_initialized || !this->_adafruitSensor || (!this->_hardwareSerial
        #if (defined(__AVR__) || defined(ESP8266)) && defined(USE_SW_SERIAL)
            && !this->_softwareSerial
        #endif
        ))
            return;

        ((Adafruit_GPS*)(this->_adafruitSensor))->standby();
    }

    void Orion::Sensors::GPS::MTK3339::WakeUp() {
        if (!this->_initialized || !this->_adafruitSensor || (!this->_hardwareSerial
        #if (defined(__AVR__) || defined(ESP8266)) && defined(USE_SW_SERIAL)
            && !this->_softwareSerial
        #endif
        ))
            return;

        ((Adafruit_GPS*)(this->_adafruitSensor))->wakeup();
    }


    bool Orion::Sensors::GPS::MTK3339::SetReadFrequency(uint16_t milliHz) {
        if (!this->_initialized || !this->_adafruitSensor || (milliHz != 100 && milliHz != 200 && milliHz != 1000 && milliHz != 2000 && milliHz != 5000 && milliHz != 10000))
            return false;

        switch (milliHz) {
            case 100:
                ((Adafruit_GPS*)(this->_adafruitSensor))->sendCommand(PMTK_SET_NMEA_UPDATE_100_MILLIHERTZ);
                break;
            case 200:
                ((Adafruit_GPS*)(this->_adafruitSensor))->sendCommand(PMTK_SET_NMEA_UPDATE_200_MILLIHERTZ);
                break;
            case 1000:
                ((Adafruit_GPS*)(this->_adafruitSensor))->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
                break;
            case 2000:
                ((Adafruit_GPS*)(this->_adafruitSensor))->sendCommand(PMTK_SET_NMEA_UPDATE_2HZ);
                break;
            case 5000:
                ((Adafruit_GPS*)(this->_adafruitSensor))->sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);
                break;
            case 10000:
                ((Adafruit_GPS*)(this->_adafruitSensor))->sendCommand(PMTK_SET_NMEA_UPDATE_10HZ);
                break;
            default:
                return false;
        }

        this->_readFrequency = milliHz;

        return true;
    }

    uint16_t Orion::Sensors::GPS::MTK3339::GetReadFrequency() {
        return this->_readFrequency;
    }


    void Orion::Sensors::GPS::MTK3339::Reset() {
        if (!this->_initialized || !this->_adafruitSensor || (!this->_hardwareSerial
        #if (defined(__AVR__) || defined(ESP8266)) && defined(USE_SW_SERIAL)
            && !this->_softwareSerial
        #endif
        ))
            return;

        ((Adafruit_GPS*)(this->_adafruitSensor))->begin(9600);
        ((Adafruit_GPS*)(this->_adafruitSensor))->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
        this->SetReadFrequency(1000);
        ((Adafruit_GPS*)(this->_adafruitSensor))->sendCommand(PGCMD_ANTENNA);
        delay(100);

        if (this->_hardwareSerial)
            this->_hardwareSerial->println(PMTK_Q_RELEASE);
        #if (defined(__AVR__) || defined(ESP8266)) && defined(USE_SW_SERIAL)
            else if (this->_softwareSerial)
                this->_softwareSerial->println(PMTK_Q_RELEASE);
        #endif
        this->WakeUp();
    }


    Orion::Sensors::GPS::MTK3339::~MTK3339() {
        if (!this->_initialized)
            return;

        if (this->_hardwareSerial) {
            free(this->_hardwareSerial);
            this->_hardwareSerial = NULL;
        }
        #if (defined(__AVR__) || defined(ESP8266)) && defined(USE_SW_SERIAL)
            if (this->_softwareSerial) {
                free(this->_softwareSerial);
                this->_softwareSerial = NULL;
            }
        #endif

        if (this->_adafruitSensor) {
            delete (Adafruit_GPS*)(this->_adafruitSensor);
            this->_adafruitSensor = NULL;
        }
        this->_initialized = false;
    }

#endif