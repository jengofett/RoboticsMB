#include <turn_wheels_using_remote> 
#include <microM.h>   // Use the microM library for motor control, IR command

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

const int senseOnOffPin=1;

int sensorInput[3]={0}; // sensor inputs

int counter=0;
const int numSamples=30;

// collect multiple samples for each sensor
unsigned int sensorSamples[numSensors][numSamples]={0};

const int DISTANCE_CLOSE=0;
const int DISTANCE_MEDIUM=1;
const int DISTANCE_FAR=2;

unsigned int zeroOffset[numSensors]={320, 320, 320};

void setup()
{
  microM.Setup(); // set up the library
  pinMode(senseOnOffPin,OUTPUT); // set up sensor on/off pin
  Serial.begin(19200); // set the serial port speed.
  digitalWrite(senseOnOffPin, HIGH);  // Turn on the sensor
}

/**
 * average the last "numSample" samples
 **/
void computeSampleAverage(unsigned int *averagedSamples)
{
  int sampleIndex=counter % numSamples;

  // collect raw data into sample array
  for (int i = 0; i < numSensors; i++)
  {
    sensorSamples[i][sampleIndex]=analogRead(sensePin[i]);
    ;
    averagedSamples[i]=0; // clear the computed average
    for (int j=0; j < numSamples; j++)
    {
      // compute average samples for the sensor
      averagedSamples[i] += sensorSamples[i][j];
    }
    averagedSamples[i]=averagedSamples[i]/numSamples;
  }
  counter++;
}

void applyThresholds(unsigned int *averageInput, int *normalizedValues)
{
  const int closeThreshold[numSensors]={400,400,375};
  const int farThreshold[numSensors]={100, 99, 70};
  const int mediumThreshold[numSensors]={225,200,200};
  
  for (int i = 0; i < numSensors; i++)
  {
    normalizedValues[i]=averageInput[i] - zeroOffset[i];
    /*Serial.print("NV-");
    Serial.print(normalizedValues[i]);
    Serial.print(" ");*/
    if (normalizedValues[i] > closeThreshold[i])
    {
      normalizedValues[i] = DISTANCE_CLOSE;
    } else if (normalizedValues[i] > mediumThreshold[i])
    {
      normalizedValues[i] = DISTANCE_MEDIUM;
    } else
    {
      normalizedValues[i] = DISTANCE_FAR;
    }
    delay(5);
  }
  /* Serial.println();*/
}

/**
 * Determine whether or not the values changed
 **/
bool valuesChanged(int *values)
{
  bool changed=false;
  static int lastValues[numSensors]={0,0,0};
  for (int i =0; i < numSensors; i++)
  {
     if (values[i] != lastValues[i])
     {
       changed=true;
       lastValues[i]=values[i]; // set the last value
     }
  }
  return changed;
}


void autoDrive(int *normalizedValues)
{
//  for (int i = 0; i < numSensors; i ++)
 
//  int i = normalizedValues 
  if ((normalizedValues[0] == 2)  && (normalizedValues[1] == 2) && (normalizedValues[2] == 2))  // nothing in front 
  {
    microM.Motors(50,52,0,0);  // go straight
    delay (150);
  }
  else if (((normalizedValues[0] == 0) && (normalizedValues[1] >= 1)) && (normalizedValues[2] >= 1))  //left blocked
  {
    microM.Motors(50,0,0,0);  // go right
    delay(300);
    microM.Motors(50,52,0,0); //go straight
    delay (150);
  }
  else if (((normalizedValues[2] == 0) && (normalizedValues[1] >= 1)) && (normalizedValues[0] >= 1))  //right blocked
  {
    microM.Motors(0,50,0,0);  // go left
    delay(300);
    microM.Motors(50,52,0,0); //go straight
    delay (150);
  }
  else if (((normalizedValues[0] == 0) && (normalizedValues[1] == 0)) && (normalizedValues[2] == 0))  //dead end
  {
    microM.Motors(0,0,0,0);  // stop
    delay(300);
    microM.Motors(-50,-52,0,0); //backup
    delay (300);
    microM.Motors(0,45,0,0);  // go left
    delay(300);
    microM.Motors(50,52,0,0); //go straight
    delay (100);
  }
  
  /* if ((normalizedValues[1]) == 1)  // something coming up
  {
    microM.Motors(30,15,0,0);  // slow down
  }
  if ((normalizedValues[0]) == 0 && (normalizedValues[1]) == 0 && (normalizedValues[2]) == 0)
  { 
    microM.Motors(0,0,0,0);
    delay(1000);
    do
    {
      microM.Motors(-90,-90,0,0);
    } while ((normalizedValues[0]) < 2 && (normalizedValues[2]) < 2);
    if ((normalizedValues[0]) == 2)
    {
      microM.Motors(0,90,0,0);
      delay(2000);
      microM.Motors(110,110,0,0);
    }
    else if ((normalizedValues[2]) == 2)
    {
      microM.Motors(90,0,0,0);
      delay(2000);
      microM.Motors(110,110,0,0);
    }
  } 
  if ((normalizedValues[1]) == 0 && (normalizedValues[0] >= 1)) // something blocking front and right
  {
    microM.Motors(0,20,0,0); //turn left
    delay(50);
    microM.Motors(50,50,0,0);  // go straight
  }
 else if ((normalizedValues[1]) == 0 && (normalizedValues[2] >= 1))  // something blocking front and left
  {
    microM.Motors(20,0,0,0);  //turn right
    delay(50);
    microM.Motors(50,50,0,0); //go straight
  }
 if ((normalizedValues[0]) >= 1 && (normalizedValues[1] >= 1)) // room at left and center
 {
   microM.Motors(20,30,0,0); //edge to left
   delay(50);
   microM.Motors(50,50,0,0);
 }
 else if ((normalizedValues[0]) >= 1 && (normalizedValues[2] >= 2)) // 
 {
   microM.Motors(50,20,0,0); //edge to right
   delay(200);
   microM.Motors(50,50,0,0);
 }
  */
}


/**
 * Calibrate the zero level.  Point the sensors at nothing
 * then run this calibration function to set the zero level. 
 **/
void calibrateZeroLevel()
{
  Serial.print("Calibrating zero level with ");
  Serial.print(numSamples);
  Serial.print(" samples");
  //
  // collect numSamples first, then compute the average
  //
  for (int n=0; n < numSamples; n++)
  {
    for (int i = 0; i < numSensors; i++)
    {
      sensorSamples[i][n]=analogRead(sensePin[i]);
    }
    delay(20); // wait a bit between reads

    Serial.print(".");
  }
  Serial.println();
  // fill in the zero offset with the sample average.
  computeSampleAverage(zeroOffset);
  Serial.print("Calibrated zero offsets:  ");
  for (int i = 0; i < numSensors; i++)
  {
    Serial.print(zeroOffset[i]);
    Serial.print(" ");
  }  
  Serial.println();
}


void loop()
{
  unsigned int averageInput[numSensors]={0};
  int normalizedValues[numSensors]={0};
  const int menuButton=28;
  //
  // ircommand sometimes produces spurrious values, so
  // we add a allowCalibrate variable to guard against this.
  // press topMenu to allow calibration, then press menu to 
  // calibrate
  //
  const int topmenu=45; // Lock calibrate
  const int popmenu=42; // Allow calibrate
  const int upKey=58;  // Drives robot forward
  const int downKey=59; //Drives robot backwards
  const int leftKey=61; //Drives robot to the left
  const int rightKey=60; //Drives robot to the right
  const int power=62; //stops robot
  const int exit=100;
  const int info=59;
  const int mute=21;
  static bool allowCalibrate=false;
  
  if (microM.ircommand > 0)
  {
    switch (microM.ircommand)
    {
      case popmenu:
        allowCalibrate = true;
        Serial.println("Allow Calibrate");
        break;
      case topmenu:
        allowCalibrate=false;
        Serial.println("Calibration Locked");
        break;
      case mute:
        if (allowCalibrate) 
        {
          calibrateZeroLevel();
          microM.ircommand = 0;
          allowCalibrate=false;
        }
        break;
      case upKey:
        microM.Motors(200,200,0,0);
        microM.ircommand = 0;
        delay(40);
        break;
      case downKey:
        microM.Motors(-200,-200,0,0);
        microM.ircommand = 0;
        delay(40);
        break;
      case leftKey:
        microM.Motors(0,200,0,0);
        microM.ircommand = 0;
        delay(40);
        break;
      case rightKey:
        microM.Motors(200,0,0,0);
        microM.ircommand = 0;
        delay(40);
        break;
      case power:
        microM.Motors(0,0,0,0);
        microM.ircommand = 0;
        delay(40);
        break;      
       case exit:
        while (microM.ircommand == exit)
        {
         
          computeSampleAverage(averageInput);
         
          applyThresholds(averageInput, normalizedValues);
         
          if (valuesChanged(normalizedValues))
          {
            for (int i = 0; i < numSensors; i++)
            {
              Serial.print(normalizedValues[i]);
              Serial.print(" ");
              autoDrive(normalizedValues);
  
              
             }
          Serial.println();
         allowCalibrate=false;
          }
          microM.ircommand = exit;
          delay(3);
        }
    }
    microM.Motors(0,0,0,0);
    microM.ircommand=0;
  
  } 

 // const int rightKey=61;
  //const int power=62;
  const int forwardSpeedL=105;
  const int forwardSpeedR=100;
  const int reverseSpeedL=-90;
  const int reverseSpeedR=-100;
  const int t=50;
  
  if (microM.ircommand>0)                         // display command from IR receiver 
  {
     Serial.print("\tIR command:");
    Serial.println(microM.ircommand,DEC);       // use the DEC option to convert a byte to a decimal number                          // prevents display repeating the same values
  }
 
  if (microM.ircommand == upKey)
   {
     microM.Motors(forwardSpeedL,forwardSpeedR,0,0);
     microM.ircommand = 0;
     delay (t);
   }   
 else if (microM.ircommand == downKey)
   {
     microM.Motors(reverseSpeedL,reverseSpeedR,0,0);
     microM.ircommand = 0;
     delay (t);
   }
else if (microM.ircommand == rightKey)
   {
     microM.Motors(forwardSpeedL,0,0,0);
     microM.ircommand = 0;
     delay (t);
   }
else if (microM.ircommand == leftKey)
   {
     microM.Motors(0,forwardSpeedR,0,0);
     microM.ircommand = 0;
     delay (t);
   }
else if   (microM.ircommand == power)
   {
     microM.Motors(0,0,0,0);
     microM.ircommand = 0;
     delay (t);
   }
   
   else
   {
     microM.Motors(0,0,0,0);
     microM.ircommand = 0;
   }
}

