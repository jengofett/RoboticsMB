/*
  Blink SOS
  Turns on an LEDpin on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LEDpin connected on most Arduino boards.
// give it a name:
int ledpin = 13;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledpin, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(ledpin, HIGH);   // turn the LEDpin on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledpin, LOW);    // turn the LEDpin off by making the voltage LOW
  delay(100);               // wait for a second
  digitalWrite(ledpin, HIGH);   // turn the LEDpin on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledpin, LOW);    // turn the LEDpin off by making the voltage LOW
  delay(100);
  digitalWrite(ledpin, HIGH);   // turn the LEDpin on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledpin, LOW);    // turn the LEDpin off by making the voltage LOW
  delay(100);
    digitalWrite(ledpin, HIGH);   // turn the LEDpin on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(ledpin, LOW);    // turn the LEDpin off by making the voltage LOW
  delay(1000);               // wait for a second
  digitalWrite(ledpin, HIGH);   // turn the LEDpin on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(ledpin, LOW);    // turn the LEDpin off by making the voltage LOW
  delay(1000);
  digitalWrite(ledpin, HIGH);   // turn the LEDpin on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(ledpin, LOW);    // turn the LEDpin off by making the voltage LOW
  delay(1000);
  digitalWrite(ledpin, HIGH);   // turn the LEDpin on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledpin, LOW);    // turn the LEDpin off by making the voltage LOW
  delay(100);               // wait for a second
  digitalWrite(ledpin, HIGH);   // turn the LEDpin on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledpin, LOW);    // turn the LEDpin off by making the voltage LOW
  delay(100);
  digitalWrite(ledpin, HIGH);   // turn the LEDpin on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledpin, LOW);    // turn the LEDpin off by making the voltage LOW
  delay(100);
  delay(1000);
}
