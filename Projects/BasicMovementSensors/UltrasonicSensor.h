/////////////////////////////////////////////////
// Tennessee Tech Autonomous Robotics Club     //
// Third Day: Boe Bot Navigation               //
//            19 September, 2017               //
// Prepared by Chris Stringer, 19 Sept, 2017   //
/////////////////////////////////////////////////

#ifndef _ULTRASONIC_SENSOR_H_
#define _ULTRASONIC_SENSOR_H_

    #include <Arduino.h>


    class UltrasonicSensor
    {
    public:
        enum SensorStyle
        {
          FourPin,
          ThreePin
        };
    
        UltrasonicSensor(int pin);
        UltrasonicSensor(int triggerPin, int receivePin);
        virtual ~UltrasonicSensor();
  
        unsigned int GetReading_us();
        float GetDistance_cm();
    
    private:
        int triggerPin_;
        int receivePin_;
        SensorStyle sensorStyle_;

        void TriggerSensor();
    };

#endif // _ULTRASONIC_SENSOR_H_
