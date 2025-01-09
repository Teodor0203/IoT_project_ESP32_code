#ifndef SENSORRFP602_H
#define SENSORRFP602_H

class SensorRFP602{
    private:
        int pin;
    public:
        SensorRFP602(int);
        void readData();    
};

#endif