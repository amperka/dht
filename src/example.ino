
// подключаем библиотеку
#include <dht.h>

// создаём объект-сенсор
DHT sensor = DHT();

void setup()
{
    Serial.begin(9600);

    // методом attach объявляем к какому контакту подключен
    // сенсор. В нашем примере это нулевой аналоговый контакт
    sensor.attach(A0);
    //
    // после подачи питания ждём секунду до готовности сенсора к работе
    delay(1000);
}

void loop()
{
    // метод update заставляет сенсор выдать текущие измерения
    sensor.update();

    switch (sensor.getLastError())
    {
        case DHT_ERROR_OK:
            char msg[128];
            // данные последнего измерения можно считать соответствующими
            // методами
            sprintf(msg, "Temperature = %dC, Humidity = %d%%", 
                    sensor.getTemperatureInt(), sensor.getHumidityInt());
            Serial.println(msg);
            break;
        case DHT_ERROR_START_FAILED_1:
            Serial.println("Error: start failed (stage 1)");
            break;
        case DHT_ERROR_START_FAILED_2:
            Serial.println("Error: start failed (stage 2)");
            break;
        case DHT_ERROR_READ_TIMEOUT:
            Serial.println("Error: read timeout");
            break;
        case DHT_ERROR_CHECKSUM_FAILURE:
            Serial.println("Error: checksum error");
            break;
    }

    delay(2000);
}
