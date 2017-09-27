/////////////////////////////////////////////////
// Tennessee Tech Autonomous Robotics Club     //
// Third Day: Boe Bot Navigation               //
//            19 September, 2017               //
// Prepared by Chris Stringer, 19 Sept, 2017   //
/////////////////////////////////////////////////

#include "UltrasonicSensor.h"    


// CONSTANTS
const float SPEED_OF_SOUND_cm_per_us = 0.0343;


//! Configure a 3-pin ultrasonic distance sensor
// in: pin = Arduino pin to trigger the sensor and to read the distance from the sensor
UltrasonicSensor::UltrasonicSensor(const int pin) :
    triggerPin_(pin),
    receivePin_(pin),
    sensorStyle_(SensorStyle::ThreePin)
{}

//! Configure a 4-pin ultrasonic distance sensor
// in: triggerPin = Arduino pin to trigger the sensor
//     receivePin = Arduino pin to read the distance from the sensor
UltrasonicSensor::UltrasonicSensor(const int triggerPin, const int receivePin) :
    triggerPin_(triggerPin),
    receivePin_(receivePin),
    sensorStyle_(SensorStyle::FourPin)
{
    pinMode(triggerPin_, OUTPUT);
    pinMode(receivePin_, INPUT);
}

//! Set the only possible output to high impedance mode for safety
UltrasonicSensor::~UltrasonicSensor()
{
    pinMode(triggerPin_, INPUT);
}

//! Get the raw time value from the distance sensor. This will be double the time 
//     representing to the distance to the object.
// out: Duration of pulse from sensor in Microseconds.
unsigned int UltrasonicSensor::GetReading_us()
{
    TriggerSensor();
    return pulseIn(receivePin_, HIGH);
}

//! Get the distance reading from the sensor
// out: Distance reported by sensor in Centimeters.
float UltrasonicSensor::GetDistance_cm()
{
    //   The time read from the sensor is a round-trip time; 
    // it needs to be cut in half to get the actual distance.
    return (GetReading_us() * SPEED_OF_SOUND_cm_per_us) / 2.0;
}

//! Trigger the distance reading from the sensor according to its pin layout
void UltrasonicSensor::TriggerSensor()
{
    switch(sensorStyle_)
    {
    case ThreePin:
        pinMode(triggerPin_, OUTPUT); // Prepare the pin to send the pulse
        digitalWrite(triggerPin_, HIGH); // Send the pulse
        delayMicroseconds(10);
        digitalWrite(triggerPin_, LOW);
        pinMode(triggerPin_, INPUT); // Prepare the pin to read data
    
    case FourPin:
        digitalWrite(triggerPin_, HIGH); // Just send the pulse
        delayMicroseconds(10);
        digitalWrite(triggerPin_, LOW);
    }
}

