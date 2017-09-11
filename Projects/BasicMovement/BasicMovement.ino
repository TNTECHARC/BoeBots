/////////////////////////////////////////////////
// Tennessee Tech Autonomous Robotics Club     //
// First Day: Intro to Boe Bots                //
//            5 September, 2017                //
// Prepared by Chris Stringer, 2 Sept, 2017    //
/////////////////////////////////////////////////


// Tell the system we're using servos.
#include <Servo.h>

// Tell the system to prepare two servos.
Servo leftWheel;
Servo rightWheel;


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

    // Look at the sections below for documentation on these functions
    TurnLeft(100, 1000); // What are these numbers?
    MoveForward(100, 1000);
    TurnRight(100, 1000);
    MoveForward(-100, 2000); // What does this do?
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

