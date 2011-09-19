
#include "dht.h"

void DHT::attach(int pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
}

DHTError DHT::update()
{
    _lastError = DHT_ERROR_OK;
    byte res;

    // prepare sensor for reading
    digitalWrite(_pin, LOW);
    delay(18 + 5);
    digitalWrite(_pin, HIGH);
    
    // DHT datasheet says host should keep line high 20-40us, 
    // then watch for sensor taking line low. 
    // That low should last 80us. Acknowledges "start read
    // and report" command.
    delayMicroseconds(40); 

    // Next: Change Arduino pin to an input, to
    // watch for the 80us low explained a moment ago.
    pinMode(_pin, INPUT);
    delayMicroseconds(40);

    res = digitalRead(_pin);

    if (res) {
        _lastError = DHT_ERROR_START_FAILED_1;
        return _lastError;
    }

    delayMicroseconds(80);
    res = digitalRead(_pin);

    if (!res) {
        _lastError = DHT_ERROR_START_FAILED_2;
        return _lastError;
    }

    // After 80us low, the line should be taken high for 80us by the
    // sensor. The low following that high is the start of the first
    // bit of the forty to come. The method readByte()
    // expects to be called with the system already into this low.
    delayMicroseconds(80);

    // now ready for data reception... pick up the 5 bytes coming from
    // the sensor
    for (byte i = 0; i < 5; i++)
        if (!readByte(_data + i))
            _lastError = DHT_ERROR_READ_TIMEOUT;

    // Restore pin to output duties
    pinMode(_pin, OUTPUT); // was: DDRC |= _BV(dht_PIN);
    digitalWrite(_pin, HIGH); // was: PORTC |= _BV(dht_PIN);

    if (!_lastError) {
        // See if data received consistent with checksum received
        byte checkSum = _data[0] + _data[1] + _data[2] + _data[3];
        if (_data[4] != checkSum)
            _lastError = DHT_ERROR_CHECKSUM_FAILURE;
    }

    return _lastError;
}

bool DHT::readByte(byte* out) const
{
    // Restrict waiting to prevent hanging
    unsigned long numloops = 0;
    unsigned long maxloops = microsecondsToClockCycles(100) / 16;

    // Collect 8 bits from datastream, return them interpreted
    // as a byte. I.e. if 0000.0101 is sent, return decimal 5.

    byte result = 0;
    for (byte i = 8; i--; ) {
        // We enter this during the first start bit (low for 50uS) of the byte
        // Wait until pin goes high
        numloops = 0;
        while (digitalRead(_pin) == LOW)
            if (++numloops == maxloops)
                return false;

        // Dataline will now stay high for 27 or 70 uS, depending on
        // whether a 0 or a 1 is being sent, respectively. Take to
        // a middle of that period to read the value
        delayMicroseconds(45);

        if (digitalRead(_pin) == HIGH)
            result |= 1 << i; // set subsequent bit

        // Wait until pin goes low again, which signals the START
        // of the NEXT bit's transmission.
        numloops = 0;
        while (digitalRead(_pin) == HIGH)
            if (++numloops == maxloops)
                return false;
    }

    *out = result;
    return true;
}

byte DHT::getTemperatureInt() const
{
    return _data[2];
}

byte DHT::getTemperatureFrac() const
{
    return _data[3];
}

byte DHT::getHumidityInt() const
{
    return _data[0];
}

byte DHT::getHumidityFrac() const
{
    return _data[1];
}
