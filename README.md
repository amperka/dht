Introduction
------------

This is an Arduino-library for easy reading of temperature/humidity sensors
based on DHT11, DHT22 (aka Aosong AM2302).

Authors
-------

Library is heavily based on publication at 
http://sheepdogguides.com/arduino/ar3ne1humDHT11.htm

Encapsulation in a reusable library, some code-size optimization and
few fixes are done by Amperka Team (http://amperka.ru)

Installation and Usage
----------------------

Copy lib/dht directory to /path/to/your/arduino-ide/libraries

Usage example is in src/main.cpp

If you're on Linux and prefer to work in console:

    # checkout the library
    git clone git@github.com:amperka/dht.git
    cd dht

    # prepare cmake-based build environment
    mkdir build
    cd build
    cmake ..

    # build, upload and run picocom as serial monitor
    make upload
    make example-serial

License
-------

The code is provided in terms of MIT license: 
http://www.opensource.org/licenses/mit-license.php
