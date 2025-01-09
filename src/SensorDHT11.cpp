#include <Arduino.h>
#include <ArduinoJson.h>
#include "SensorDHT11.h"
#include "BluetoothSerial.h"


BluetoothSerial serialBT_DHT11;

SensorDHT11::SensorDHT11(int pin) : pin(pin), dht(pin, DHT11) {    
    dht.begin();
}

void SensorDHT11::readData()
{
    StaticJsonDocument<200> docDHT11;
    
    serialBT_DHT11.begin();

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    float feelTemperature = dht.computeHeatIndex(temperature, humidity, false);

    if(isnan(humidity) || isnan(temperature) || isnan(feelTemperature))
    {
        docDHT11["dataDHT11"]["noData"] = "Failed to read data from MPU6050 sensor!";
        return;
    }

    docDHT11["sensorType"] = "DHT11";
    docDHT11["timeStamp"] = millis();
    docDHT11["dataDHT11"]["humidity"] = humidity;
    docDHT11["dataDHT11"]["temperature"] = temperature;
    docDHT11["dataDHT11"]["feelTemperature"] = feelTemperature;

    String outputDHT11;
    serializeJson(docDHT11, outputDHT11);

    //Serial.println(outputDHT11);
    serialBT_DHT11.println(outputDHT11);
}

