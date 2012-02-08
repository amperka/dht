
#ifndef DHT_H
#define DHT_H

#ifndef ARDUINO
#error "Arduino version not defined"
#endif

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

enum DHTError
{
    DHT_ERROR_OK = 0,
    DHT_ERROR_START_FAILED_1 = 1,
    DHT_ERROR_START_FAILED_2 = 2,
    DHT_ERROR_READ_TIMEOUT = 3,
    DHT_ERROR_CHECKSUM_FAILURE = 4,
};

class DHT
{
    public:
        void attach(int pin);
        DHTError update();

        byte getTemperatureInt() const;
        byte getTemperatureFrac() const;

        byte getHumidityInt() const;
        byte getHumidityFrac() const;

        DHTError getLastError() const { return _lastError; }

    private:
        bool readByte(byte* out) const;

    private:
        int _pin;
        byte _data[5];
        DHTError _lastError;
};

#endif
