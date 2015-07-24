
//Modified blink sos using loop function

//I will use a loop function to simplify the BLINK SOS program

int ledpin = 13;


// the setup routine runs once when you press reset
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledpin, OUTPUT);     
}

void shortBlinks()
{
  for(int i=0; i<3; i++)
  {
    digitalWrite(ledpin, HIGH);   // turn the LEDpin on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledpin, LOW);    // turn the LEDpin off by making the voltage LOW
  delay(100);               // wait for a second
  }
}

void longBlinks()
{
  for (int i=0; i<3; i++)
{
 digitalWrite(ledpin, HIGH);   // turn the LEDpin on (HIGH is the voltage level)
     delay(1000);               // wait for a second
  digitalWrite(ledpin, LOW);    // turn the LEDpin off by making the voltage LOW
  delay(1000);               // wait for a second
}
}

// the loop routine runs over and over again forever:
void loop() 
 
 //THIS IS THE FIRST SERIES OF 3 SHORT BLINKS
{
  shortBlinks();
  
  
  //THIS IS THE SERIES OF 3 LONG BLINKS
  
longBlinks();

  
  //THIS IS THE SERIES OF 3 SHORT BLINKS
  shortBlinks();
  delay(1000);
}
