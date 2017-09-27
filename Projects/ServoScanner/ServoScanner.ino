#include <Servo.h>

Servo scanner;
const int pingTxPin = 8;
const int pingRxPin = 7;

const int NUM_REPS = 10;

void setup() 
{
    Serial.begin(115200);
  
    scanner.attach(9);
    
}

void loop() 
{
    for (int i = 0; i < 180; i++)
    {
        scanner.write(i);
        delay(10);

        // Get average of several readings
        int distance_cm = 0;
        for (int rep = 0; rep < NUM_REPS; rep++)
        {
            distance_cm += GetDistance_cm();
        }
        distance_cm /= NUM_REPS;

        Serial.print(i);
        Serial.print(":");
        Serial.println(distance_cm);
        
    }

    for (int i = 180; i >= 0; i--)
    {
        scanner.write(i);
        delay(10);

        // Get average of several readings
        int distance_cm = 0;
        for (int rep = 0; rep < NUM_REPS; rep++)
        {
            distance_cm += GetDistance_cm();
        }
        distance_cm /= NUM_REPS;

        Serial.print(i);
        Serial.print(":");
        Serial.println(distance_cm);
        
    }
}

float GetDistance_cm()
{
  long duration = 0;
  float cm = 0.0;
  
  // Tell the sensor to start recording
  pinMode(pingTxPin, OUTPUT);
  digitalWrite(pingTxPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingTxPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingTxPin, LOW);

  // Listen to the response
  pinMode(pingRxPin, INPUT);
  duration = pulseIn(pingRxPin, HIGH, 1000000);

  cm = (duration / 2) * 0.0343; // us * (cm/us)
  return cm;
}


