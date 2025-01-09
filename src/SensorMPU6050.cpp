#include <Arduino.h>
#include <ArduinoJson.h>
#include "BluetoothSerial.h"
#include "SensorMPU6050.h"
#include "SensorGPS.h"
#define GRAVITATION_ACC 9.81;

BluetoothSerial serialBT_MPU6050;
extern SensorGPS sensorGPS;


SensorMPU6050::SensorMPU6050(){

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void SensorMPU6050::readData(){
    StaticJsonDocument<200> docMPU6050;
    mpu.begin();
    
    serialBT_MPU6050.begin();

    Serial.begin(115200);
    while (!Serial)
      delay(10); // will pause Zero, Leonardo, etc until serial console opens


    // Try to initialize!
    if (!mpu.begin()) {

      while (1) {
        delay(10);
      }
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    switch (mpu.getAccelerometerRange()) {
      case MPU6050_RANGE_2_G:
        Serial.println("+-2G");
        break;
      case MPU6050_RANGE_4_G:
        Serial.println("+-4G");
        break;
      case MPU6050_RANGE_8_G:
        Serial.println("+-8G");
        break;
      case MPU6050_RANGE_16_G:
        Serial.println("+-16G");
        break;
    }

    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    Serial.print("Gyro range set to: ");
    switch (mpu.getGyroRange()) {
      case MPU6050_RANGE_250_DEG:
        Serial.println("+- 250 deg/s");
        break;
      case MPU6050_RANGE_500_DEG:
        Serial.println("+- 500 deg/s");
        break;
      case MPU6050_RANGE_1000_DEG:
        Serial.println("+- 1000 deg/s");
        break;
      case MPU6050_RANGE_2000_DEG:
        Serial.println("+- 2000 deg/s");
        break;
    }

    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    Serial.print("Filter bandwidth set to: ");
    switch (mpu.getFilterBandwidth()) {
      case MPU6050_BAND_260_HZ:
        Serial.println("260 Hz");
        break;
      case MPU6050_BAND_184_HZ:
        Serial.println("184 Hz");
        break;
      case MPU6050_BAND_94_HZ:
        Serial.println("94 Hz");
        break;
      case MPU6050_BAND_44_HZ:
        Serial.println("44 Hz");
        break;
      case MPU6050_BAND_21_HZ:
        Serial.println("21 Hz");
        break;
      case MPU6050_BAND_10_HZ:
        Serial.println("10 Hz");
        break;
      case MPU6050_BAND_5_HZ:
        Serial.println("5 Hz");
        break;
    }

    Serial.println("");
    delay(100);

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    if (isnan(a.acceleration.x) || isnan(a.acceleration.y) || isnan(a.acceleration.z)) {
    docMPU6050["dataMPU6050"]["noData"] = "Failed to read data from MPU6050 sensor!";
    return;
  }
  
  const double JUMP_THRESHOLD = -3.0;
  const double LANDING_THRESHOLD = 3.0;
  
  float zAcceleration = a.acceleration.z - GRAVITATION_ACC;
  bool airborne;
  int jumpDetected = 0;

  if(zAcceleration < JUMP_THRESHOLD)
  {
    jumpDetected = 1;
    sensorGPS.readData();
  }
  else if(zAcceleration > LANDING_THRESHOLD)
  {
    jumpDetected = -1;
  }
   

  docMPU6050["sensorType"] = "MPU6050";
  docMPU6050["timeStamp"] = millis();
  docMPU6050["dataMPU6050"]["jumpDetected"] = jumpDetected;
  docMPU6050["dataMPU6050"]["accelerationZ"] = zAcceleration;
  // docMPU6050["dataMPU6050"]["gyroX"] = g.gyro.x;
  // docMPU6050["dataMPU6050"]["gyroY"] = g.gyro.y;
  // docMPU6050["dataMPU6050"]["gyroZ"] = g.gyro.z;
  // docMPU6050["dataMPU6050"]["temperature"] = temp.temperature;

  String outputMPU6050;
  serializeJson(docMPU6050, outputMPU6050);
  serialBT_MPU6050.println(outputMPU6050);
  
  
}

