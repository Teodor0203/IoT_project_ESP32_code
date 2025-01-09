#ifndef SENSORMPU6050_H
#define SENSORMPU6050_H

#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

class SensorMPU6050 {
    private:
        Adafruit_MPU6050 mpu;
    public:
        SensorMPU6050();
        void readData();    
};

#endif