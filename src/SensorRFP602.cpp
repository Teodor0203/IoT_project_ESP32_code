#include <Arduino.h>
#include <ArduinoJson.h>
#include "BluetoothSerial.h"
#include "SensorRFP602.h"

BluetoothSerial serialBT_RFP602;

SensorRFP602::SensorRFP602(int pin) : pin(pin) 
{
    this -> pin = pin;
}

void SensorRFP602::readData()
{
    StaticJsonDocument<200> docRFP602;
    
    serialBT_RFP602.begin();
    int analogPressure = analogRead(pin); 

    if(isnan(analogPressure))
    {
        docRFP602["dataRFP602"]["noData"] = "Failed to read data from RFP602 sensor!";
        return;
    }

    docRFP602["sensorType"] = "RFP602";
    docRFP602["timeStamp"] = millis();
    docRFP602["dataRFP602"]["analogPressureValue"] = analogPressure;

    String outputRFP602;
    serializeJson(docRFP602, outputRFP602);
    
    //Serial.println(outputRFP602);
    serialBT_RFP602.println(outputRFP602);
}
