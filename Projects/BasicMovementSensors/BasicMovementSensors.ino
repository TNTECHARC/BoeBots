/////////////////////////////////////////////////
// Tennessee Tech Autonomous Robotics Club     //
// Third Day: Boe Bot Navigation               //
//            19 September, 2017               //
// Prepared by Chris Stringer, 19 Sept, 2017   //
/////////////////////////////////////////////////

//   This program adds an ultrasonic sensor to the previous movement demo.
// It implements basic navigation by always turning left when the robot
// encounters an obstacle.  

// Connect the right wheel to pin 12
//         the left wheel to pin 13
//         the PING))) sensor to pin 8


// Tell the system we're using servos and ultrasonic distance sensors
#include <Servo.h>
#include "UltrasonicSensor.h"

// Tell the system to prepare two servos.
Servo leftWheel;
Servo rightWheel;

// Configure a 3-pin PING))) ultrasonic distance sensor
UltrasonicSensor distanceSensor(8);
// UltrasonicSensor distanceSensor(7, 8); // Use this line if you have a 4 pin sensor (trigger, receive)

///////////////// MAIN PROGRAM ////////////////////////////

// This block runs once when the robot starts
void setup() 
{
    // Tell the system where to find the servos.
    leftWheel.attach(13);
    rightWheel.attach(12);

    // Put commands to run once here
}

// This block will repeat until the robot runs out of battery.
void loop() 
{
    // Put commands to be run repeatedly here 

    // Move the robot forward and check the sensor 10 times per second.
    // Question: The robot does not move very far each time it checks the sensor.
    //           What happens when you make it move forward for a longer time? Shorter?
    // Advanced Question: GetDistance() can take a long time, and the robot will move forward inconsistently.
    //           Can you fix this? Can you minimize it?
    while(distanceSensor.GetDistance_cm() > 5)
    {
        MoveForward(100, 100); // Move forward for 0.1 seconds
    }
    TurnLeft(100, 500); // Turn left to avoid the obstacle and try again
}


///////////////// MOVEMENT FUNCTIONS ////////////////////////////

//! Move Robot Forward
// in: speed = Speed in percent (-100% to 100%); Make this negative to move backward
//     time_ms = Duration of movement, in milliseconds
// question: Does using this function to move backward make sense? What can you change for this to make more sense?
void MoveForward(int speed, int time_ms)
{
    MoveLeftWheel(speed);
    MoveRightWheel(speed);
    delay(time_ms);
    Stop();
}

//! Turn the chassis to the right
// in: speed = Speed in percent (0%-100%)
//     time_ms = Duration of movement, in milliseconds
// question: What if speed is negative? How can you stop this?
void TurnRight(int speed, int time_ms)
{
    MoveLeftWheel(speed);
    MoveRightWheel(-speed);
    delay(time_ms);
    Stop();
}

//! Turn the chassis to the left
// in: speed = Speed in percent (0%-100%)
//     time_ms = Duration of movement, in milliseconds
void TurnLeft(int speed, int time_ms)
{
    MoveLeftWheel(-speed);
    MoveRightWheel(speed);
    delay(time_ms);
    Stop();
}

//! Stop chassis movement
void Stop()
{
    MoveLeftWheel(0);
    MoveRightWheel(0);
}


///////////////// HARDWARE CONTROL FUNCTIONS ////////////////////////////

//! Move the left wheel forward
// in: speed = Speed in percent (-100% to 100%); Make this negative to move backward
// question: Why do we need to map the values to the servo? What signal does the servo expect?
//           What happens if |speed| > 100?
void MoveLeftWheel(int speed)
{
    int servoSpeed = map(speed, -100, 100, 0, 180); // Change speed to a servo angle
    leftWheel.write(servoSpeed);
}

//! Move the right wheel forward
// in: speed = Speed in percent (-100% to 100%); Make this negative to move backward
// question: What is different between this function and MoveLeftWheel (besides the wheel name)? Why?
void MoveRightWheel(int speed)
{
    int servoSpeed = map(speed, -100, 100, 180, 0); // Change speed to a servo angle
    rightWheel.write(servoSpeed);
}

