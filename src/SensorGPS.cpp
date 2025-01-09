#include <Arduino.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "BluetoothSerial.h"
#include "SensorGPS.h"

#define GPSBaud 9600

BluetoothSerial serialBT_gps;
TinyGPSPlus gpsModule;


SensorGPS::SensorGPS(int rx, int tx) : rxPin(rx), txPin(tx), gpsSerial(2){ 
    gpsSerial.begin(GPSBaud, SERIAL_8N1, rxPin, txPin);
}

void SensorGPS::readData()
{
    serialBT_gps.begin();

    while(gpsSerial.available() > 0) {
        gpsModule.encode(gpsSerial.read());
        if(gpsModule.location.isUpdated())
        {
            float latitude = gpsModule.location.lat();
            float longitude = gpsModule.location.lng();
            float speed = gpsModule.speed.kmph() > 0 ? gpsModule.speed.kmph() : 0.00;

            StaticJsonDocument<200> docGPS;

            docGPS["sensorType"] = "NEO6M";
            docGPS["timeStamp"] = millis();
            docGPS["dataNEO6M"]["latitude"] = latitude;
            docGPS["dataNEO6M"]["longitude"] = longitude;
            docGPS["dataNEO6M"]["speed"] = speed;

            String outputGPS;
            serializeJson(docGPS, outputGPS);

            serialBT_gps.println(outputGPS);
        }
    }
}