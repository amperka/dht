
#include <WProgram.h>

#define ANALOG_PIN_OFFSET 14

enum DHTError
{
    DHT_ERROR_OK = 0,
    DHT_ERROR_START_FAILED_1 = 1,
    DHT_ERROR_START_FAILED_2 = 2,
    DHT_ERROR_CHECKSUM_FAILURE = 3,
};

class DHT
{
    public:
        void attach(int analogPin);
        DHTError update();

        byte getTemperatureInt() const;
        byte getTemperatureFrac() const;
        float getTemperature() const;

        byte getHumidityInt() const;
        byte getHumidityFrac() const;
        float getHumidity() const;

        DHTError getLastError() const { return _lastError; }

    private:
        byte readByte() const;

    private:
        int _pin;
        byte _data[5];
        DHTError _lastError;
};
