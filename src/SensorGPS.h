#ifndef SENSORGPS_H
#define SENSORGPS_H
#include <TinyGPS++.h>

class SensorGPS{
    private:
        int rxPin;
        int txPin;
        HardwareSerial gpsSerial;
    
    public:
        SensorGPS(int, int);
        void readData();
};

#endif