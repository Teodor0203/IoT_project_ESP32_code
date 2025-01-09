#ifndef SensorDHT11_H
#define SensorDHT11_H
#include "DHT.h"

class SensorDHT11{
    private:
        int pin;
        DHT dht;

    public:
        SensorDHT11(int);
        void readData();
};

#endif