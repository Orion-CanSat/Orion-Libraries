#pragma once

#ifdef ARDUINO
    #include <Arduino.h>
    #include <SoftwareSerial.h>

    #include "Orion/Orion.hpp"
    #include "Orion/Sensors/Sensor.hpp"
    #include "Orion/Sensors/GPS/Coordinates.hpp"
    #include "Orion/Sensors/GPS/GPS.hpp"

    namespace Orion {
        namespace Sensors {
            namespace GPS {
                class MTK3339 : public Orion::Sensors::GPS::GPS {
                    protected:
                        void* _adafruitSensor = NULL;
                        HardwareSerial* _hardwareSerial = NULL;
                        #if (defined(__AVR__) || defined(ESP8266)) && defined(USE_SW_SERIAL)
                            SoftwareSerial* _softwareSerial = NULL;
                        #endif
                        uint16_t _readFrequency = 0;
                    public:
                        MTK3339(HardwareSerial* serial);
                        #if (defined(__AVR__) || defined(ESP8266)) && defined(USE_SW_SERIAL)
                            MTK3339(SoftwareSerial* serial);
                        #endif

                        virtual void Update();

                        virtual bool Send(uint8_t* message, uint64_t len);
                        virtual uint64_t Receive(uint8_t* message, uint64_t len);

                        virtual void Sleep();
                        virtual void WakeUp();

                        virtual bool SetReadFrequency(uint16_t milliHz);
                        virtual uint16_t GetReadFrequency();

                        virtual void Reset();

                        ~MTK3339();
                };
            }
        }
    }

#endif