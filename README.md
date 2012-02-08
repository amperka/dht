Introduction
------------

This is an Arduino-library for easy reading of temperature/humidity sensors
based on DHT11, DHT22 (aka Aosong AM2302).

The library is compatible with Arduino Software version 1.x as well as old 0.x.

Authors
-------

Library is heavily based on publication at 
http://sheepdogguides.com/arduino/ar3ne1humDHT11.htm

Encapsulation in a reusable library, some code-size optimization and
few fixes are done by Amperka Team (http://amperka.ru)

Installation and Usage
----------------------

Copy lib/dht directory to /path/to/your/arduino-ide/libraries

Usage example is in src/example.ino

If you prefer to work in console and have [ino](http://inotool.org) installed:

    # checkout the library
    git clone git@github.com:amperka/dht.git
    cd dht

    # build, upload and run serial monitor
    ino build
    ino upload
    ino serial

License
-------

The code is provided in terms of MIT license: 
http://www.opensource.org/licenses/mit-license.php
