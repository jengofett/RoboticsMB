#include <microM.h>  // Use the microM libraryfor motor control,  IR command


enum SensorPosition {
  SenseLeft=0,
  SenseCenter=1,
  SenseRight=2,
}; 
const int numSensors=3;
//
// Sensing pins
//
const int sensePin[3]={5,4,3};  // array containing the pin numbers
// for right,center, and left

const int sensor0n0ffPin=1; 

int sensorInput[3]={0}; // sensor inputs

void setup()
{
  microM.Setup(); // set up the library
  pinMode(sensor0n0ffPin,OUTPUT); // set up sensor on/off pin
  Serial.begin(19200); // set the serial port speed.
  digitalWrite(sensor0n0ffPin, HIGH);  //Turn on the sensor
}

void loop()
{for (int i = 0; i < numSensors; i++)
{
  sensorInput[i]=analogRead(sensePin[i]);
  sensorInput[i]=sensorInput[i]-550;
  
  Serial.print(sensorInput[i]);
  Serial.print(" ");
}
Serial.println();
}

