
set(DHT_LIB dht)

set(${DHT_LIB}_BOARD uno)
set(${DHT_LIB}_HDRS dht.h)
set(${DHT_LIB}_SRCS dht.cpp)

generate_arduino_library(${DHT_LIB})
