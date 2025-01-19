#include "SensorDHT11.h"
#include "SensorRFP602.h"
#include "SensorMPU6050.h"
#include "SensorGPS.h"
#include "BluetoothSerial.h"

BluetoothSerial serialBT;

#pragma region Sensors
SensorRFP602 sensorRFP602(4); //Analog pin D4
SensorRFP602 sensorRFP602No2(2);
SensorGPS sensorGPS(16, 17);
SensorMPU6050 sensorMPU6050;
#pragma endregion Sensors

#pragma region MillisInterval
unsigned long previousMillisDHT11 = 0UL;
unsigned long previousMillisRFP602 = 0UL;
unsigned long previousMillisRFP602_2 = 0UL;
unsigned long previousMillisMPU6050 = 0UL;
unsigned long previousMillisNEO6M = 0UL;

unsigned long DHT11_interval = 5000UL;
unsigned long RFP602_interval = 1000UL;
unsigned long RFP602_interval_2 = 1000UL;
unsigned long MPU6050_interval = 100UL;
unsigned long NEO6M_interval = 5000UL;
#pragma endregion MillisInterval


void setup() {
  
  serialBT.begin("ESP32");
  delay(2000);
  serialBT.println("Hello :D");
  //sensorRFP602.readData();
  //sensorRFP602No2.readData();
  sensorMPU6050.readData();
  //sensorGPS.readData();
}

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillisMPU6050 > MPU6050_interval)
  {
    sensorMPU6050.readData(); 

    previousMillisMPU6050 = currentMillis;
  }
  
  if(currentMillis - previousMillisRFP602 > RFP602_interval)
  {
    //sensorRFP602.readData();

    previousMillisRFP602 = currentMillis;
  }

  if(currentMillis - previousMillisRFP602_2 > RFP602_interval_2)
  {
//    sensorRFP602No2.readData();

    previousMillisRFP602_2 = currentMillis;
  }

  if(currentMillis - previousMillisNEO6M > NEO6M_interval)
  {
    //sensorGPS.readData();

    previousMillisNEO6M = currentMillis;
  }
}
