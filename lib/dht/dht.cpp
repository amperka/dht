
#include "dht.h"

void DHT::attach(int analogPin)
{
    _pin = analogPin + ANALOG_PIN_OFFSET;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
}

DHTError DHT::update()
{
    byte res;

    // prepare sensor for reading
    digitalWrite(_pin, LOW);
    delay(18 + 5);
    digitalWrite(_pin, HIGH);
    // DHT22 datasheet says host should keep line high 20-40us, 
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

    /*After 80us low, the line should be taken high for 80us by the
      sensor. The low following that high is the start of the first
      bit of the forty to come. The routine "read_dht_dat()"
      expects to be called with the system already into this low.*/
    delayMicroseconds(80);
    //now ready for data reception... pick up the 5 bytes coming from
    //   the sensor
    for (byte i = 0; i < 5; i++)
        _data[i] = readByte();

    //Next: restore pin to output duties
    pinMode(_pin, OUTPUT);//Was: DDRC |= _BV(dht_PIN);
    //N.B.: Using DDRC put restrictions on value of dht_pin

    //Next: Make data line high again, as output from Arduino
    digitalWrite(_pin, HIGH);//Was: PORTC |= _BV(dht_PIN);
    //N.B.: Using PORTC put restrictions on value of dht_pin

    //Next see if data received consistent with checksum received
    byte checkSum = _data[0] + _data[1] + _data[2] + _data[3];
    /*Condition in following "if" says "if fifth byte from sensor
      not the same as the sum of the first four..."*/
    if (_data[4] != checkSum)
        _lastError = DHT_ERROR_CHECKSUM_FAILURE;
    else
        _lastError = DHT_ERROR_OK;

    return _lastError;
}

byte DHT::readByte() const
{
    //Collect 8 bits from datastream, return them interpreted
    //as a byte. I.e. if 0000.0101 is sent, return decimal 5.

    //Code expects the system to have recently entered the
    //dataline low condition at the start of every data bit's
    //transmission BEFORE this function is called.

    byte result = 0;
    for (byte i = 0; i < 8; i++) {
        //We enter this during the first start bit (low for 50uS) of the byte
        //Next: wait until pin goes high
        while (digitalRead(_pin) == LOW)
            ;
        //signalling end of start of bit's transmission.

        //Dataline will now stay high for 27 or 70 uS, depending on
        //whether a 0 or a 1 is being sent, respectively.
        delayMicroseconds(30);//AFTER pin is high, wait further period, to be
        //into the part of the timing diagram where a 0 or a 1 denotes
        //the datum being send. The "further period" was 30uS in the software
        //that this has been created from. I believe that a higher number
        //(45?) would be more appropriate.

        //Next: Wait while pin still high
        if (digitalRead(_pin) == HIGH)
            result |= 1 << (7 - i);// "add" (not just addition) the 1
        //to the growing byte
        //Next wait until pin goes low again, which signals the START
        //of the NEXT bit's transmission.
        while (digitalRead(_pin) == HIGH)
            ;
    }

    return result;
}

byte DHT::getTemperatureInt() const
{
    return _data[2];
}

byte DHT::getTemperatureFrac() const
{
    return _data[3];
}

float DHT::getTemperature() const
{
    return (float)getTemperatureInt() + (float)getTemperatureFrac() / 100.f;
}

byte DHT::getHumidityInt() const
{
    return _data[0];
}

byte DHT::getHumidityFrac() const
{
    return _data[1];
}

float DHT::getHumidity() const
{
    return (float)getHumidityInt() + (float)getHumidityFrac() / 100.f;
}
